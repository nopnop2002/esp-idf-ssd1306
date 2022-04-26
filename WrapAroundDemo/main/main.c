#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

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
	ESP_LOGI(TAG, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
#endif // CONFIG_SSD1306_128x32

	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);

#if CONFIG_SSD1306_128x64
	ssd1306_display_text(&dev, 0, "SSD1306 128x64", 14, false);
	ssd1306_display_text(&dev, 1, "ABCDEFGHIJKLMNOP", 16, false);
	ssd1306_display_text(&dev, 2, "abcdefghijklmnop",16, false);
	ssd1306_display_text(&dev, 3, "Hello World!!", 13, false);
	ssd1306_display_text(&dev, 4, "SSD1306 128x64", 14, true);
	ssd1306_display_text(&dev, 5, "ABCDEFGHIJKLMNOP", 16, true);
	ssd1306_display_text(&dev, 6, "abcdefghijklmnop",16, true);
	ssd1306_display_text(&dev, 7, "Hello World!!", 13, true);
	int pages = 7;
#endif // CONFIG_SSD1306_128x64

#if CONFIG_SSD1306_128x32
	ssd1306_display_text(&dev, 0, "SSD1306 128x32", 14, false);
	ssd1306_display_text(&dev, 1, "Hello World!!", 13, false);
	ssd1306_display_text(&dev, 2, "SSD1306 128x32", 14, true);
	ssd1306_display_text(&dev, 3, "Hello World!!", 13, true);
	int pages = 3;
#endif // CONFIG_SSD1306_128x32

	vTaskDelay(3000 / portTICK_PERIOD_MS);
	while(1) {
		for(int i=0;i<128;i++) {
			ssd1306_wrap_arround(&dev, SCROLL_RIGHT, 1, 2, 0);
			if (pages == 7) {
				ssd1306_wrap_arround(&dev, SCROLL_RIGHT, 5, 6, 0);
			}
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		for(int i=0;i<128;i++) {
			ssd1306_wrap_arround(&dev, SCROLL_LEFT, 1, 2, 0);
			if (pages == 7) {
				ssd1306_wrap_arround(&dev, SCROLL_LEFT, 5, 6, 0);
			}
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		int height = ssd1306_get_height(&dev);
		ESP_LOGD(TAG, "height=%d", height);
		for(int i=0;i<height;i++) {
			ssd1306_wrap_arround(&dev, SCROLL_UP, 0, 31, 0);
			ssd1306_wrap_arround(&dev, SCROLL_UP, 96, 127, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		ESP_LOGD(TAG, "height=%d", height);
		for(int i=0;i<height;i++) {
			ssd1306_wrap_arround(&dev, SCROLL_DOWN, 0, 31, 0);
			ssd1306_wrap_arround(&dev, SCROLL_DOWN, 96, 127, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		for(int i=0;i<128;i++) {
			ssd1306_wrap_arround(&dev, SCROLL_RIGHT, 0, pages, 0);
			ssd1306_wrap_arround(&dev, SCROLL_DOWN, 0, 127, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);

		for(int i=0;i<128;i++) {
			ssd1306_wrap_arround(&dev, SCROLL_LEFT, 0, pages, 0);
			ssd1306_wrap_arround(&dev, SCROLL_UP, 0, 127, 0);
		}
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	} // end while
}
