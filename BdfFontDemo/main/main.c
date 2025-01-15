#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_err.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "ncenR12.h"
#include "timR12.h"
#include "emoticons.h"
#include "Scroll-o-Sprites.h"

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

typedef struct {
	unsigned char encoding;
	unsigned char width;
	unsigned char bbw;
	unsigned char bbh;
	unsigned char bbx;
	unsigned char bby;
	unsigned char num_data;
	unsigned char y_start;
	unsigned char y_end;
} BDF_FONT_t;

esp_err_t load_bitmap_font(unsigned char *font, int encoding, unsigned char *bitmap, BDF_FONT_t *bdf_font)
{
	ESP_LOGI(tag, "encoding=%d", encoding);
	int index = 2;
	while (1) {
		ESP_LOGD(tag, "font[%d]=%d size=%d", index, font[index], font[index+6]);
		if (font[index+6] == 0) break;
		if (font[index] == encoding) {
			bdf_font->encoding = font[index];
			bdf_font->width = font[index+1];
			bdf_font->bbw = font[index+2];
			bdf_font->bbh = font[index+3];
			bdf_font->bbx = font[index+4];
			bdf_font->bby = font[index+5];
			bdf_font->num_data = font[index+6];
			bdf_font->y_start = font[index+7];
			bdf_font->y_end = font[index+8];
			for (int i=0;i<font[index+6];i++) {
				ESP_LOGD(tag, "font[%d]=0x%x", index+9+i, font[index+9+i]);
				bitmap[i] = font[index+9+i];
			}
			return ESP_OK;
		}
		index = index + font[index+6] + 9;;
	} // end while
	return ESP_ERR_NOT_FOUND;
}

esp_err_t show_bdf_font_text(SSD1306_t * dev, unsigned char *font, char *text, int xpos, int ypos)
{
	int fontboundingbox_width = font[0];
	int fontboundingbox_height = font[1];
	size_t bitmap_size = ((fontboundingbox_width + 7) / 8) * fontboundingbox_height;
	ESP_LOGD(tag, "fontboundingbox_width=%d fontboundingbox_height=%d bitmap_size=%d",
		fontboundingbox_width, fontboundingbox_height, bitmap_size);
	unsigned char *bitmap = malloc(bitmap_size);
	if (bitmap == NULL) {
		ESP_LOGE(tag, "malloc fail");
		return ESP_ERR_NO_MEM;
	}
	BDF_FONT_t bdf_font;
	int _xpos = xpos;
	for (int i=0;i<strlen(text);i++) {
		memset(bitmap, 0, bitmap_size);
		int ch = text[i];
		esp_err_t err = load_bitmap_font(font, ch, bitmap, &bdf_font);
		if (err != ESP_OK) {
			ESP_LOGE(tag, "font not found [%d]", ch);
			continue;
		}
		//ESP_LOG_BUFFER_HEXDUMP(tag, bitmap, bdf_font.num_data, ESP_LOG_INFO);
		ESP_LOGD(tag, "bdf_font.width=%d", bdf_font.width);
		ESP_LOGD(tag, "bdf_font.bbx=%d, bby=%d", bdf_font.bbx, bdf_font.bby);
		ESP_LOGD(tag, "bdf_font.y_start=%d, y_end=%d", bdf_font.y_start, bdf_font.y_end);
		int bitmap_height = bdf_font.y_end - bdf_font.y_start + 1;
		int bitmap_width = bdf_font.num_data / bitmap_height;
		ESP_LOGD(tag, "bitmap_width=%d bitmap_height=%d", bitmap_width, bitmap_height);
		_ssd1306_bitmaps(dev, _xpos, ypos+bdf_font.y_start, bitmap, bitmap_width*8, bitmap_height, false);
		_xpos = _xpos + bdf_font.width;
	}
	ssd1306_show_buffer(dev);
	free(bitmap);
	return ESP_OK;
}

esp_err_t show_bdf_font_code(SSD1306_t * dev, unsigned char *font, int code, int xpos, int ypos)
{
	int fontboundingbox_width = font[0];
	int fontboundingbox_height = font[1];
	size_t bitmap_size = ((fontboundingbox_width + 7) / 8) * fontboundingbox_height;
	ESP_LOGD(tag, "fontboundingbox_width=%d fontboundingbox_height=%d bitmap_size=%d",
		fontboundingbox_width, fontboundingbox_height, bitmap_size);
	unsigned char *bitmap = malloc(bitmap_size);
	if (bitmap == NULL) {
		ESP_LOGE(tag, "malloc fail");
		return ESP_ERR_NO_MEM;
	}
	BDF_FONT_t bdf_font;
	memset(bitmap, 0, bitmap_size);
	esp_err_t err = load_bitmap_font(font, code, bitmap, &bdf_font);
	if (err != ESP_OK) {
		ESP_LOGE(tag, "font not found [%d]", code);
		return err;
	}
	//ESP_LOG_BUFFER_HEXDUMP(tag, bitmap, bdf_font.num_data, ESP_LOG_INFO);
	ESP_LOGD(tag, "bdf_font.width=%d", bdf_font.width);
	ESP_LOGD(tag, "bdf_font.bbx=%d, bby=%d", bdf_font.bbx, bdf_font.bby);
	ESP_LOGD(tag, "bdf_font.y_start=%d, y_end=%d", bdf_font.y_start, bdf_font.y_end);
	int bitmap_height = bdf_font.y_end - bdf_font.y_start + 1;
	int bitmap_width = bdf_font.num_data / bitmap_height;
	ESP_LOGD(tag, "bitmap_width=%d bitmap_height=%d", bitmap_width, bitmap_height);
	ESP_LOG_BUFFER_HEXDUMP(tag, bitmap, bdf_font.num_data, ESP_LOG_DEBUG);
	ssd1306_bitmaps(dev, xpos, ypos+bdf_font.y_start, bitmap, bitmap_width*8, bitmap_height, false);
	free(bitmap);
	return ESP_OK;
}

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

#if CONFIG_FLIP
	dev._flip = true;
	ESP_LOGW(tag, "Flip upside down");
#endif

#if CONFIG_SSD1306_128x64
	ESP_LOGI(tag, "Panel is 128x64");
	ssd1306_init(&dev, 128, 64);
#endif // CONFIG_SSD1306_128x64
#if CONFIG_SSD1306_128x32
	ESP_LOGI(tag, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
#endif // CONFIG_SSD1306_128x32

	while (1) {
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		show_bdf_font_text(&dev, __ncenR12_bitmap__, "Hello World", 0, 0); // You can change font file
#if CONFIG_SSD1306_128x64
		show_bdf_font_text(&dev, __timR12_bitmap__, "Hello World", 0, 32); // You can change font file
#endif
		vTaskDelay(500);

#if 0
		// Non-Ascii character
		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		int xpos = 0;
		for (int code=161;code<170;code++) {
			show_bdf_font_code(&dev, __ncenR12_bitmap__, code, xpos, 0);
			xpos = xpos + 12;
		}
#if CONFIG_SSD1306_128x64
		xpos = 0;
		for (int code=181;code<190;code++) {
			show_bdf_font_code(&dev, __ncenR12_bitmap__, code, xpos, 32);
			xpos = xpos + 12;
		}
#endif
		vTaskDelay(500);
#endif

		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 32, 0, 5);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 33, 24, 5);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 34, 48, 5);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 35, 72, 5);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 36, 96, 5);
#if CONFIG_SSD1306_128x64
		show_bdf_font_code(&dev, __emoticons_bitmap__, 48, 0, 37);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 49, 24, 37);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 50, 48, 37);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 51, 72, 37);
		show_bdf_font_code(&dev, __emoticons_bitmap__, 52, 96, 37);
#endif
		vTaskDelay(500);

		ssd1306_clear_screen(&dev, false);
		ssd1306_contrast(&dev, 0xff);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 57, 0, 5);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 69, 20, 5);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 70, 40, 5);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 81, 60, 5);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 88, 80, 5);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 93, 100, 5);
#if CONFIG_SSD1306_128x64
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 1, 0, 37);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 6, 20, 37);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 26, 40, 37);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 27, 60, 37);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 33, 80, 37);
		show_bdf_font_code(&dev, __Scroll_o_Sprites_bitmap__, 46, 100, 37);
#endif
		vTaskDelay(500);
	}


}
