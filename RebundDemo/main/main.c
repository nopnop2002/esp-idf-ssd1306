#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_random.h"
#include "esp_log.h"

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

#define tag "SSD1306"

void app_main(void)
{
	SSD1306_t dev;

#if CONFIG_I2C_INTERFACE
	ESP_LOGI(tag, "INTERFACE is i2c");
	ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(tag, "INTERFACE is SPI");
	ESP_LOGI(tag, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(tag, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(tag, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(tag, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_SPI_INTERFACE

#if CONFIG_SSD1306_128x64
	ESP_LOGI(tag, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
	int xmax = 127;
	int ymax = 63;
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(tag, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
	int xmax = 127;
	int ymax = 31;
#endif // CONFIG_SSD1306_128x32

	int radius = 4;
	uint32_t xrand = esp_random();
	uint32_t yrand = esp_random();
	ESP_LOGD(tag, "xrand=%"PRIu32" yrand=%"PRIu32, xrand, yrand);
	//int x_current = 10;
	//int y_current = 10;
	int x_current = xrand % xmax;
	int y_current = yrand % ymax;
	ESP_LOGD(tag, "x_current=%d", x_current);
	ESP_LOGD(tag, "y_current=%d", y_current);
	int x_previus = x_current;
	int y_previus = y_current;
	int x_direction = 1;
	int y_direction = 1;
	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);

	while(1) {
		_ssd1306_circle(&dev, x_previus, y_previus, radius, OLED_DRAW_ALL, true);
		_ssd1306_circle(&dev, x_current, y_current, radius, OLED_DRAW_ALL, false);
		ssd1306_show_buffer(&dev);
		x_previus = x_current;
		y_previus = y_current;
		x_current = x_current + x_direction;
		y_current = y_current + y_direction;
		if ( (x_current + radius) >= xmax) {
			x_direction = -1;
		} else if ( (x_current - radius) <= 0) {
			x_direction = 1;
		} else if ( (y_current + radius) >= ymax) {
			y_direction = -1;
		} else if ( (y_current - radius) <= 0) {
			y_direction = 1;
		}
		vTaskDelay(1);
	}
}
