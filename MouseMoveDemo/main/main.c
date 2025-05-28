#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
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

	bool draw = false;
	ssd1306_clear_screen(&dev, draw); // background is black
	ssd1306_contrast(&dev, 0xff);

	// Draw a circle in the center
	int radius = 4;
	ESP_LOGD(TAG, "x_current=%d", x_current);
	ESP_LOGD(TAG, "y_current=%d", y_current);
	_ssd1306_circle(&dev, x_current, y_current, radius, OLED_DRAW_ALL, draw);
	ssd1306_show_buffer(&dev);

	// Wait event
	HID_EVENT_t hidEvent;
	while (1) {
		int x_previus = x_current;
		int y_previus = y_current;
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
			_ssd1306_circle(&dev, x_previus, y_previus, radius, OLED_DRAW_ALL, !draw);
			_ssd1306_circle(&dev, x_current, y_current, radius, OLED_DRAW_ALL, draw);
			ssd1306_show_buffer(&dev);
			if (hidEvent.mouse_event.button1 == 1) {
				draw = true; // background is white
				ssd1306_clear_screen(&dev, draw);
				_ssd1306_circle(&dev, x_current, y_current, radius, OLED_DRAW_ALL, draw);
				ssd1306_show_buffer(&dev);
			} else if (hidEvent.mouse_event.button2 == 1) {
				draw = false; // background is black
				ssd1306_clear_screen(&dev, draw);
				_ssd1306_circle(&dev, x_current, y_current, radius, OLED_DRAW_ALL, draw);
				ssd1306_show_buffer(&dev);
			}
		}
	}
}
