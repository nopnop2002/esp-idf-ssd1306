#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

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

#if CONFIG_SSD1306_128x64
	ESP_LOGI(TAG, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
	int xmax = 127;
	int ymax = 63;
	int x_current = 63;
	int y_current = 31;
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(TAG, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
	int xmax = 127;
	int ymax = 31;
	int x_current = 63;
	int y_current = 15;
#endif // CONFIG_SSD1306_128x32

	// Create queue
	app_event_hid = xQueueCreate(10, sizeof(HID_EVENT_t));
	configASSERT( app_event_hid );

	// Start tasks
	xTaskCreate(&usb_hid_task, "usb_hid_task", 1024*2, NULL, 9, NULL);

	// Allocate memory
	uint8_t *buffer = (uint8_t *)malloc(8*128); // 8 page 128 pixel
	if (buffer == NULL) {
		ESP_LOGE(TAG, "malloc failed");
		while(1) { vTaskDelay(1); }
	}

	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
	ssd1306_display_text_x3(&dev, 0, "01234", 5, false);
#if CONFIG_SSD1306_128x64
	ssd1306_display_text_x3(&dev, 4, "56789", 5, false);
#endif
	ssd1306_get_buffer(&dev, buffer);

	// Draw a cursor in the center
	int radius = 4;
	ESP_LOGD(TAG, "x_current=%d", x_current);
	ESP_LOGD(TAG, "y_current=%d", y_current);
	_ssd1306_cursor(&dev, x_current, y_current, radius, false);
	ssd1306_show_buffer(&dev);

	// Wait event
	HID_EVENT_t hidEvent;
	while (1) {
		BaseType_t received = xQueueReceive(app_event_hid, &hidEvent, portMAX_DELAY);
		ESP_LOGI(TAG, "xQueueReceive received=%d hidEvent.hid_event_type=%d", received, hidEvent.hid_event_type);
		if (hidEvent.hid_event_type == APP_EVENT_MOUSE) {
			ESP_LOGI(TAG, "mouse_event.x_displacement=%d mouse_event.y_displacement=%d",
				hidEvent.mouse_event.x_displacement, hidEvent.mouse_event.y_displacement);
			ESP_LOGI(TAG, "mouse_event.button1=%d mouse_event.button2=%d mouse_event.button3=%d",
				hidEvent.mouse_event.button1, hidEvent.mouse_event.button2, hidEvent.mouse_event.button3);
			int x_temp = x_current + hidEvent.mouse_event.x_displacement;
			if ((x_temp+radius) <= xmax && (x_temp-radius) >= 0) x_current = x_temp;
			int y_temp = y_current + hidEvent.mouse_event.y_displacement;
			if ((y_temp+radius) <= ymax && (y_temp-radius) >= 0) y_current = y_temp;
			ssd1306_set_buffer(&dev, buffer);
			_ssd1306_cursor(&dev, x_current, y_current, radius, false);
			ssd1306_show_buffer(&dev);
			if (hidEvent.mouse_event.button1 == 1) {
				printf("x_current=%d y_current=%d\n", x_current, y_current);
				if (y_current > 20 && y_current < 32) continue;
				if (y_current > 52) continue;
				int selected = -1;
				if (x_current >= 24*0 && x_current <= 24*1-5) {
					selected = 0;
				} else if (x_current >= 24*1 && x_current <= 24*2-5) {
					selected = 1;
				} else if (x_current >= 24*2 && x_current <= 24*3-5) {
					selected = 2;
				} else if (x_current >= 24*3 && x_current <= 24*4-5) {
					selected = 3;
				} else if (x_current >= 24*4 && x_current <= 24*5-5) {
					selected = 4;
				}
				if (selected == -1) continue;
				if (y_current >= 32) selected = selected + 5;
				printf("selected=%d\n", selected);
				ssd1306_clear_screen(&dev, false);
				char text[12];
				sprintf(text, "%d", selected);
				ssd1306_display_text_x3(&dev, 0, text, 1, false);
				vTaskDelay(300);
			}
		}
	}
}
