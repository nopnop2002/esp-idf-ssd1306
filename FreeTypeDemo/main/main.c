/*
 * SPDX-FileCopyrightText: 2024 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
//#include "esp_err.h"
#include "esp_spiffs.h"
#include "ft2build.h"
#include FT_FREETYPE_H

#include "ssd1306.h"

static const char *tag = "MAIN";

#define BITMAP_WIDTH  20
#define BITMAP_HEIGHT 16

static FT_Library  s_library;
static FT_Face s_face;
static uint8_t s_bitmap[BITMAP_HEIGHT][BITMAP_WIDTH];

static void load_font(char *font)
{
	FT_Error error = FT_New_Face( s_library, font, 0, &s_face );
	if (error) {
		ESP_LOGE(tag, "Error loading font: %d", error);
		abort();
	}
	ESP_LOGI(tag, "Font [%s] loaded", font);
}

static void render_text(SSD1306_t * dev, int xpos, int ypos, int threshold, char *text)
{
	/* Configure character size. */
	//const int font_size = 14;
	const int font_size = 16;
	const int freetype_scale = 64;
	FT_Error error = FT_Set_Char_Size(s_face, 0, font_size * freetype_scale, 0, 0 );
	if (error) {
		ESP_LOGE(tag, "Error setting font size: %d", error);
		abort();
	}

	int num_chars = strlen(text);

	/* current drawing position */
	int x = 0;
	int y = 12;

	for (int n = 0; n < num_chars; n++) {
		memset(s_bitmap, 0, BITMAP_WIDTH*BITMAP_HEIGHT);
		ESP_LOGI(tag, "Rendering char: '%c'", text[n]);

		/* retrieve glyph index from character code */
		FT_UInt  glyph_index = FT_Get_Char_Index( s_face, text[n] );

		/* load glyph image into the slot (erase previous one) */
		error = FT_Load_Glyph( s_face, glyph_index, FT_LOAD_DEFAULT );
		//error = FT_Load_Glyph( s_face, glyph_index, FT_LOAD_MONOCHROME  | FT_LOAD_TARGET_MONO);
		if (error) {
			ESP_LOGE(tag, "Error loading glyph: %d", error);
			abort();
		}

		/* convert to a bitmap */
		error = FT_Render_Glyph( s_face->glyph, FT_RENDER_MODE_NORMAL );
		if (error) {
			ESP_LOGE(tag, "Error rendering glyph: %d", error);
			abort();
		}

		/* copy the glyph bitmap into the overall bitmap */
		FT_GlyphSlot slot = s_face->glyph;
		ESP_LOGD(tag, "font_size=%d", font_size);
		ESP_LOGD(tag, "slot->bitmap.rows=%d", slot->bitmap.rows);
		ESP_LOGD(tag, "slot->bitmap.width=%d", slot->bitmap.width);
		ESP_LOGD(tag, "slot->bitmap_top=%d", slot->bitmap_top);
		ESP_LOGD(tag, "slot->bitmap_left=%d", slot->bitmap_left);
		ESP_LOGD(tag, "slot->advance.x/64=%"PRIi32, slot->advance.x/64);
		int width = 0;
		for (int iy = 0; iy < slot->bitmap.rows; iy++) {
			for (int ix = 0; ix < slot->bitmap.width; ix++) {
				/* bounds check */
				//int res_x = ix + x;
				int res_x = ix + x + slot->bitmap_left;
				if (res_x < 0) res_x = 0;
				int res_y = y + iy - slot->bitmap_top;
				if (res_y < 0) res_y = 0;
				ESP_LOGD(tag,"res_x=%d res_y=%d", res_x, res_y);
				if (res_x >= BITMAP_WIDTH || res_y >= BITMAP_HEIGHT) {
					ESP_LOGW(tag, "bitmap size too large. res_x=%d res_y=%d", res_x, res_y);
					continue;
				}
				ESP_LOGD(tag, "iy=%d ix=%d res_y=%d res_x=%d", iy, ix, res_y, res_x);
				s_bitmap[res_y][res_x] = slot->bitmap.buffer[ix + iy * slot->bitmap.width];
				if (res_x > width) width = res_x;
			}
		}

		uint8_t bitmap[BITMAP_HEIGHT];
		memset(bitmap, 0, BITMAP_HEIGHT);
		ESP_LOGD(tag, "width=%d", width);
		for (int iy = 0; iy < BITMAP_HEIGHT; iy++) {
			for (int ix = 0; ix < width; ix++) {
				int val = s_bitmap[iy][ix];
				ESP_LOGD(tag, "val=%d", val);
				if (val > 128) {
					putchar('#');
				} else if (val > 64) {
					putchar('+');
				} else if (val > 32) {
					putchar('.');
				} else {
					putchar('_');
				}

				uint8_t wk = 0;
				if (val > threshold) wk = 1;
				wk = wk << ix;
				bitmap[iy] = bitmap[iy] | wk;
				ESP_LOGD(tag, "val=%d threshold=%d ix=%d iy=%d wk=0x%x bitmap[iy]=0x%x", val, threshold, ix, iy, wk, bitmap[iy]);
				
			}
			putchar('\n');
		}
		
		//ESP_LOG_BUFFER_HEXDUMP(tag, bitmap, BITMAP_HEIGHT, ESP_LOG_INFO);
		for (int i=0;i<BITMAP_HEIGHT;i++) {
			bitmap[i] = ssd1306_rotate_byte(bitmap[i]);
		}
		//ESP_LOG_BUFFER_HEXDUMP(tag, bitmap, BITMAP_HEIGHT, ESP_LOG_INFO);
		_ssd1306_bitmaps(dev, xpos, ypos, bitmap, 8, BITMAP_HEIGHT, false);
		xpos += slot->advance.x / 64;
	}
	ssd1306_show_buffer(dev);
}

void app_main(void)
{
	SSD1306_t dev;
	//int top, bottom;
	//char lineChar[20];

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

	// Initialize SPIFFS
	esp_vfs_spiffs_conf_t conf = {
		.base_path = "/fonts",
		.partition_label = "fonts",
		.max_files = 1,
	};
	ESP_ERROR_CHECK(esp_vfs_spiffs_register(&conf));

	// Initialize FreeType
	FT_Error error = FT_Init_FreeType( &s_library );
	if (error) {
		ESP_LOGE(tag, "Error initializing FreeType library: %d", error);
		abort();
	}
	ESP_LOGI(tag, "FreeType library initialized");

	ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);

	// Bold style
	load_font("/fonts/consola.ttf");
	render_text(&dev, 0, 0, 32, "FreeType");
	FT_Done_Face( s_face );

	// Slim style
	load_font("/fonts/consola.ttf");
	render_text(&dev, 0, 16, 128, "FreeType");
	FT_Done_Face( s_face );

#if CONFIG_SSD1306_128x64
	//load_font("/fonts/FiraMono-Regular.ttf");
	load_font("/fonts/monof55.ttf");
	render_text(&dev, 0, 32, 32, "FreeType");
	FT_Done_Face( s_face );

	load_font("/fonts/FiraMono-Regular.ttf");
	render_text(&dev, 0, 48, 64, "FreeType");
	FT_Done_Face( s_face );
#endif

	FT_Done_FreeType( s_library );
}
