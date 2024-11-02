#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
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

#define tag "SSD1306"

#if CONFIG_I2C_INTERFACE

#if CONFIG_I2C_PORT_0
#define I2C_NUM I2C_NUM_0
#elif CONFIG_I2C_PORT_1
#define I2C_NUM I2C_NUM_1
#endif

void i2c_task(void *pvParameter)
{
	// Register the device with i2c address = 0c3C
	SSD1306_t dev1;
	i2c_master_init(&dev1, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);

	// Register the device with i2c address = 0c3D to the same I2C bus
	SSD1306_t dev2;
	dev2._i2c_bus_handle = dev1._i2c_bus_handle;
	i2c_device_add(&dev2, I2C_NUM, -1, 0x3D);

	// Show Device 1
	ssd1306_init(&dev1, 128, 64);
	ssd1306_clear_screen(&dev1, false);
	ssd1306_contrast(&dev1, 0xff);
	ssd1306_display_text_x3(&dev1, 0, "Hello", 5, false);

	// Show Device 2
	ssd1306_init(&dev2, 128, 64);
	ssd1306_clear_screen(&dev2, false);
	ssd1306_contrast(&dev2, 0xff);
	ssd1306_display_text_x3(&dev2, 0, "World", 5, false);

	vTaskDelete(NULL);
}
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
void spi_task(void *pvParameter)
{
	int GPIO_CS1 = 16;
	int GPIO_CS2 = 17;

	gpio_reset_pin( GPIO_CS1 );
	gpio_set_direction( GPIO_CS1, GPIO_MODE_OUTPUT );
	gpio_set_level( GPIO_CS1, 1 );

	gpio_reset_pin( GPIO_CS2 );
	gpio_set_direction( GPIO_CS2, GPIO_MODE_OUTPUT );
	gpio_set_level( GPIO_CS2, 1 );

	SSD1306_t dev;
	spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);

	// Initialize Device 1
	gpio_set_level( GPIO_CS1, 0 );
	ssd1306_init(&dev, 128, 64);
	gpio_set_level( GPIO_CS1, 1 );

	// Initialize Device 2
	gpio_set_level( GPIO_CS2, 0 );
	ssd1306_init(&dev, 128, 64);
	gpio_set_level( GPIO_CS2, 1 );

	// Show Device 1
	gpio_set_level( GPIO_CS1, 0 );
	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
	ssd1306_display_text_x3(&dev, 0, "Hello", 5, false);
	gpio_set_level( GPIO_CS1, 1 );

	// Show Device 2
	gpio_set_level( GPIO_CS2, 0 );
	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
	ssd1306_display_text_x3(&dev, 0, "World", 5, false);
	gpio_set_level( GPIO_CS2, 1 );
	
	vTaskDelete(NULL);
}
#endif // CONFIG_SPI_INTERFACE

void app_main(void)
{
#if CONFIG_I2C_INTERFACE
	ESP_LOGI(tag, "INTERFACE is i2c");
	ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	xTaskCreate(&i2c_task, "I2C", 1024*6, NULL, 2, NULL);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_SPI_INTERFACE
	ESP_LOGI(tag, "INTERFACE is SPI");
	ESP_LOGI(tag, "CONFIG_MOSI_GPIO=%d",CONFIG_MOSI_GPIO);
	ESP_LOGI(tag, "CONFIG_SCLK_GPIO=%d",CONFIG_SCLK_GPIO);
	ESP_LOGI(tag, "CONFIG_CS_GPIO=%d",CONFIG_CS_GPIO);
	ESP_LOGI(tag, "CONFIG_DC_GPIO=%d",CONFIG_DC_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	xTaskCreate(&spi_task, "SPI", 1024*4, NULL, 2, NULL);
#endif // CONFIG_SPI_INTERFACE
}
