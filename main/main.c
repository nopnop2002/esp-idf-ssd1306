#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ssd1306.h"
#include "font8x8_basic.h"

// You have to set this config value with menuconfig
// CONFIG_MODEL
// CONFIG_SDA_GPIO
// CONFIG_SCL_GPIO
// CONFIG_RESET_GPIO

void app_main(void)
{
    SSD1306_t dev;
	i2c_master_init(CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
	if (CONFIG_MODEL == SSD1306_128x64) ssd1306_init(&dev, 128, 64, 0x3C);
	if (CONFIG_MODEL == SSD1306_128x32) ssd1306_init(&dev, 128, 32, 0x3C);
    int center = 3;
    if (CONFIG_MODEL == SSD1306_128x32) center = 1;

	ssd1306_clear_screen(dev, false);
	ssd1306_contrast(dev, 0xff);
    if (CONFIG_MODEL == SSD1306_128x64) {
		ssd1306_display_text(dev, 0, "SSD1306 128x64", 14, false);
		ssd1306_display_text(dev, 1, "ABCDEFGHIJKLMNOP", 16, false);
		ssd1306_display_text(dev, 2, "abcdefghijklmnop",16, false);
		ssd1306_display_text(dev, 3, "Hello World!!", 13, false);
		ssd1306_clear_line(dev, 4, true);
		ssd1306_clear_line(dev, 5, true);
		ssd1306_clear_line(dev, 6, true);
		ssd1306_clear_line(dev, 7, true);
		ssd1306_display_text(dev, 4, "SSD1306 128x64", 14, true);
		ssd1306_display_text(dev, 5, "ABCDEFGHIJKLMNOP", 16, true);
		ssd1306_display_text(dev, 6, "abcdefghijklmnop",16, true);
		ssd1306_display_text(dev, 7, "Hello World!!", 13, true);
	}
    if (CONFIG_MODEL == SSD1306_128x32) {
		ssd1306_display_text(dev, 0, "SSD1306 128x32", 14, false);
		ssd1306_display_text(dev, 1, "Hello World!!", 13, false);
		ssd1306_clear_line(dev, 2, true);
		ssd1306_clear_line(dev, 3, true);
		ssd1306_display_text(dev, 2, "SSD1306 128x32", 14, true);
		ssd1306_display_text(dev, 3, "Hello World!!", 13, true);
	}
	vTaskDelay(3000 / portTICK_PERIOD_MS);
    
	// Display Count Down
    uint8_t image[24];
    memset(image, 0, sizeof(image));
	ssd1306_display_image(dev, 2, (6*8-1), image, sizeof(image));
	ssd1306_display_image(dev, 3, (6*8-1), image, sizeof(image));
	ssd1306_display_image(dev, 4, (6*8-1), image, sizeof(image));
	for(int font=0x39;font>0x30;font--) {
    	memset(image, 0, sizeof(image));
		ssd1306_display_image(dev, 3, (7*8-1), image, 8);
		memcpy(image, font8x8_basic_tr[font], 8);
		ssd1306_display_image(dev, 3, (7*8-1), image, 8);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	
	// Horizontal Scroll
	ssd1306_clear_screen(dev, false);
	ssd1306_contrast(dev, 0xff);
	ssd1306_display_text(dev, center, "Horizontal", 10, false);
	ssd1306_scroll(dev, SCROLL_RIGHT);
	vTaskDelay(10000 / portTICK_PERIOD_MS);
	ssd1306_scroll(dev, SCROLL_LEFT);
	vTaskDelay(10000 / portTICK_PERIOD_MS);
	ssd1306_scroll(dev, SCROLL_STOP);
	
	// Vertical Scroll
	ssd1306_clear_screen(dev, false);
	ssd1306_contrast(dev, 0xff);
	ssd1306_display_text(dev, center, "Vertical", 8, false);
	ssd1306_scroll(dev, SCROLL_DOWN);
	vTaskDelay(10000 / portTICK_PERIOD_MS);
	ssd1306_scroll(dev, SCROLL_UP);
	vTaskDelay(10000 / portTICK_PERIOD_MS);
	ssd1306_scroll(dev, SCROLL_STOP);
	
	// Invert
	ssd1306_clear_screen(dev, true);
	ssd1306_contrast(dev, 0xff);
	ssd1306_display_text(dev, center, "  Good Bye!!", 12, true);
	
#if 0
	// Fade Out
	for(int contrast=0xff;contrast>0;contrast=contrast-0x20) {
		ssd1306_contrast(dev, contrast);
		vTaskDelay(40);
	}
#endif
}
