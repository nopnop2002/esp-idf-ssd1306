#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "RotaryEncoder.h"
#include "ssd1306.h"

/*
 You have to set this config value with menuconfig
 CONFIG_INTERFACE

 for i2c
 CONFIG_MODEL
 CONFIG_SDA_GPIO
 CONFIG_SCL_GPIO
 CONFIG_RESET_GPIO

 for SPI
 CONFIG_CS_GPIO
 CONFIG_DC_GPIO
 CONFIG_RESET_GPIO
*/

#define TAG "SSD1306"

// Draw background
void Background(SSD1306_t * dev, int x0, int y0) {
	unsigned int opt;
	opt = OLED_DRAW_UPPER_RIGHT | OLED_DRAW_UPPER_LEFT;
	int r0 = 40;
	_ssd1306_circle(dev, x0, y0, r0, opt, false);
	int r1 = 38;
	_ssd1306_circle(dev, x0, y0, r1, opt, false);
	ssd1306_show_buffer(dev);

	ssd1306_display_text_box1(dev, 0, 56, "50", 2, 2, false, 0);
	ssd1306_display_text_box1(dev, 3, 14, "25", 2, 2, false, 0);
	ssd1306_display_text_box1(dev, 3, 96, "75", 2, 2, false, 0);
	ssd1306_display_text_box1(dev, 6, 14, "0", 1, 1, false, 0);
	ssd1306_display_text_box1(dev, 6, 104, "100", 3, 3, false, 0);
}

// Draw needle
void Needle(SSD1306_t * dev, int x0, int y0, int rn, int deg) {
	float rad = deg * M_PI / 180.0;
	int x1 = x0 + (rn * cos(rad));
	int y1 = y0 + (rn * sin(rad));
	_ssd1306_line(dev, x0, y0, x1, y1, false);
	int rc = 8;
	unsigned int opt;
	opt = OLED_DRAW_UPPER_RIGHT | OLED_DRAW_UPPER_LEFT;
	_ssd1306_disc(dev, x0, y0, rc, opt, false);
	ssd1306_show_buffer(dev);
	_ssd1306_line(dev, x0, y0, x1, y1, true);
}

void app_main(void)
{
	SSD1306_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is i2c");
	ESP_LOGI(TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(TAG, "INTERFACE is SPI");
	ESP_LOGI(TAG, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(TAG, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(TAG, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(TAG, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_FLIP
	dev._flip = true;
	ESP_LOGW(TAG, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	ESP_LOGI(TAG, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGE(TAG, "Panel is 128x32. This demo cannot be run.");
	while(1) { vTaskDelay(1); }
#endif // CONFIG_SSD1306_128x32

	ssd1306_contrast(&dev, 0xff);
	ssd1306_clear_screen(&dev, false);

	// Draw background
	int x0 = 63;
	int y0 = 55;
	Background(&dev, x0, y0);

	// Draw label
	char* labelText[] = {"LOAD", "COOLANT", "INTAKE", "VOLT"};
	int labelLen[] = {4, 7, 6, 4};
	int labelPos[] = {48, 36, 40, 48};
	int labelIndex = 0;
	ssd1306_display_text_box1(&dev, 4, labelPos[labelIndex], labelText[labelIndex], labelLen[labelIndex], labelLen[labelIndex], false, 0);

	// Draw needle
	int rn = 36;
	int deg = 270; // meter position is 50
	Needle(&dev, x0, y0, rn, deg);
	
	// Initialize RotaryEncoder
	initRotaryEncoder(CONFIG_GPIO_OUT_A, CONFIG_GPIO_OUT_B, CONFIG_GPIO_SWITCH, NULL);

	int prev_count; // Previus encoder count value
	int now_count; // Current encoder count value
	int sw; // Current encoder switch value
	int interrupt; // Interrupt occurrence count
	int event = readRotaryEncoder(&prev_count, &sw, &interrupt);

	while(1) {
		event = readRotaryEncoder(&now_count, &sw, &interrupt);
		if (event == 0) {
			// When the encoder is rotated
			ESP_LOGI(TAG, "prev_count=%d now_count=%d", prev_count, now_count);
			int diff_count = now_count - prev_count;
			prev_count = now_count;
			deg = deg + diff_count;
			if (deg > 360) deg = 360;
			if (deg < 180) deg = 180;
			ESP_LOGI(TAG, "deg=%d", deg);
			// Draw needle
			ssd1306_display_text_box1(&dev, 4, labelPos[labelIndex], labelText[labelIndex], labelLen[labelIndex], labelLen[labelIndex], false, 0);
			Needle(&dev, x0, y0, rn, deg);
	
		} else if (event == 1) {
			// When the switch is pressed
			ESP_LOGI(TAG, "sw=%d", sw);
			if (sw == 0) {
				labelIndex++;
				if (labelIndex > 3) labelIndex = 0;
				// Draw background
				ssd1306_clear_screen(&dev, false);
				Background(&dev, x0, y0);
				ssd1306_display_text_box1(&dev, 4, labelPos[labelIndex], labelText[labelIndex], labelLen[labelIndex], labelLen[labelIndex], false, 0);
				// Draw needle
				Needle(&dev, x0, y0, rn, deg);
			}
		}
		vTaskDelay(1);
	}
}
