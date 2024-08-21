#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
//#include "esp_random.h"
#include "esp_log.h"

#include "ssd1306.h"

#include "usb_hid.h"

QueueHandle_t app_event_hid = NULL;

void usb_hid_task(void *pvParameters);

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
	int maxPage = 8;
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(tag, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
	int maxPage = 4;
#endif // CONFIG_SSD1306_128x32

	// Create queue
	app_event_hid = xQueueCreate(10, sizeof(HID_EVENT_t));
	configASSERT( app_event_hid );

	// Start tasks
	xTaskCreate(&usb_hid_task, "usb_hid_task", 1024*2, NULL, 9, NULL);

	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);

	// Wait event
	HID_EVENT_t hidEvent;
	char text[16];
	memset(text, 0x20, sizeof(text));
	int currentIndex = 0;
	int currentPage = 0;
	while (1) {
		BaseType_t received = xQueueReceive(app_event_hid, &hidEvent, portMAX_DELAY);
		ESP_LOGI(tag, "xQueueReceive received=%d hidEvent.hid_event_type=%d", received, hidEvent.hid_event_type);
		if (hidEvent.hid_event_type == APP_EVENT_KEYBOARD) {
			if (hidEvent.key_event.state == KEY_STATE_PRESSED) {
				ESP_LOGI(tag, "key_event.modifier=%d key_event.key_code=%d key_event.key_char=[%c]",
				hidEvent.key_event.modifier, hidEvent.key_event.key_code, hidEvent.key_event.key_char);
				if (hidEvent.key_event.key_code == 40) { // Enter
					if (currentPage+1 == maxPage) continue;
					memset(text, 0x20, sizeof(text));
					currentIndex = 0;
					currentPage++;
				} else if (hidEvent.key_event.key_code == 42) { // Back Space
					if (currentIndex == 0) continue;
					text[--currentIndex] = 0x20;
					ssd1306_display_text(&dev, currentPage, text, 16, false);
				} else {
					if (currentIndex == 16) continue;
					text[currentIndex++] = hidEvent.key_event.key_char;
					ssd1306_display_text(&dev, currentPage, text, 16, false);
				}
			}
		}
	}
}
