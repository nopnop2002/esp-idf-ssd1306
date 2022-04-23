#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

#define tag "SSD1306"
#define PACK8 __attribute__((aligned( __alignof__( uint8_t ) ), packed ))

typedef union out_column_t {
	uint32_t u32;
	uint8_t  u8[4];
} PACK8 out_column_t;

void ssd1306_init(SSD1306_t * dev, int width, int height)
{
	if (dev->_address == SPIAddress) {
		spi_init(dev, width, height);
	} else {
		i2c_init(dev, width, height);
	}
}

void ssd1306_display_text(SSD1306_t * dev, int page, char * text, int text_len, bool invert)
{
	if (page >= dev->_pages) return;
	int _text_len = text_len;
	if (_text_len > 16) _text_len = 16;

	uint8_t seg = 0;
	uint8_t image[8];
	for (uint8_t i = 0; i < _text_len; i++) {
		memcpy(image, font8x8_basic_tr[(uint8_t)text[i]], 8);
		if (invert) ssd1306_invert(image, 8);
		if (dev->_flip) ssd1306_flip(image, 8);
		if (dev->_address == SPIAddress) {
			spi_display_image(dev, page, seg, image, 8);
		} else {
			i2c_display_image(dev, page, seg, image, 8);
		}
		seg = seg + 8;
	}
}

void 
ssd1306_display_text_x3(SSD1306_t * dev, int page, char * text, int text_len, bool invert)
{
	if (page >= dev->_pages) return;
	int _text_len = text_len;
	if (_text_len > 5) _text_len = 5;

	uint8_t seg = 0;

	for (uint8_t nn = 0; nn < _text_len; nn++) {

		uint8_t const * const in_columns = font8x8_basic_tr[(uint8_t)text[nn]];

		// make the character 3x as high
		out_column_t out_columns[8];
		memset(out_columns, 0, sizeof(out_columns));

		for (uint8_t xx = 0; xx < 8; xx++) {  // for each column (x-direction)

			uint32_t in_bitmask = 0b1;
			uint32_t out_bitmask = 0b111;

			for (uint8_t yy = 0; yy < 8; yy++) {  // for pixel (y-direction)
				if (in_columns[xx] & in_bitmask) {
					out_columns[xx].u32 |= out_bitmask;
				}
				in_bitmask <<= 1;
				out_bitmask <<= 3;
			}
		}

		// render character in 8 column high pieces, making them 3x as wide
		for (uint8_t yy = 0; yy < 3; yy++)  {  // for each group of 8 pixels high (y-direction)

			uint8_t image[24];
			for (uint8_t xx = 0; xx < 8; xx++) {  // for each column (x-direction)
				image[xx*3+0] = 
				image[xx*3+1] = 
				image[xx*3+2] = out_columns[xx].u8[yy];
			}
			if (invert) ssd1306_invert(image, 24);
			if (dev->_flip) ssd1306_flip(image, 24);
			if (dev->_address == SPIAddress) {
				spi_display_image(dev, page+yy, seg, image, 24);
			} else {
				i2c_display_image(dev, page+yy, seg, image, 24);
			}
		}
		seg = seg + 24;
	}
}

void ssd1306_display_image(SSD1306_t * dev, int page, int seg, uint8_t * images, int width)
{
	if (dev->_address == SPIAddress) {
		spi_display_image(dev, page, seg, images, width);
	} else {
		i2c_display_image(dev, page, seg, images, width);
	}
}

void ssd1306_clear_screen(SSD1306_t * dev, bool invert)
{
    char space[16];
    memset(space, 0x20, sizeof(space));
    for (int page = 0; page < dev->_pages; page++) {
        ssd1306_display_text(dev, page, space, sizeof(space), invert);
    }
}

void ssd1306_clear_line(SSD1306_t * dev, int page, bool invert)
{
    char space[16];
    memset(space, 0x20, sizeof(space));
    ssd1306_display_text(dev, page, space, sizeof(space), invert);
}

void ssd1306_contrast(SSD1306_t * dev, int contrast)
{
	if (dev->_address == SPIAddress) {
		spi_contrast(dev, contrast);
	} else {
		i2c_contrast(dev, contrast);
	}
}

void ssd1306_software_scroll(SSD1306_t * dev, int start, int end)
{
	ESP_LOGD(tag, "software_scroll start=%d end=%d _pages=%d", start, end, dev->_pages);
	if (start < 0 || end < 0) {
		dev->_scEnable = false;
	} else if (start >= dev->_pages || end >= dev->_pages) {
		dev->_scEnable = false;
	} else {
		dev->_scEnable = true;
		dev->_scStart = start;
		dev->_scEnd = end;
		dev->_scDirection = 1;
		if (start > end ) dev->_scDirection = -1;
		for (int i=0;i<dev->_pages;i++) {
			dev->_page[i]._valid = false;
			dev->_page[i]._segLen = 0;
		}
	}
}


void ssd1306_scroll_text(SSD1306_t * dev, char * text, int text_len, bool invert)
{
	ESP_LOGD(tag, "dev->_scEnable=%d", dev->_scEnable);
	if (dev->_scEnable == false) return;

	void (*func)(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
	if (dev->_address == SPIAddress) {
		func = spi_display_image;
	} else {
		func = i2c_display_image;
	}

	int srcIndex = dev->_scEnd - dev->_scDirection;
	while(1) {
		int dstIndex = srcIndex + dev->_scDirection;
		ESP_LOGD(tag, "srcIndex=%d dstIndex=%d", srcIndex,dstIndex);
		dev->_page[dstIndex]._valid = dev->_page[srcIndex]._valid;
		dev->_page[dstIndex]._segLen = dev->_page[srcIndex]._segLen;
		for(int seg = 0; seg < dev->_width; seg++) {
			dev->_page[dstIndex]._segs[seg] = dev->_page[srcIndex]._segs[seg];
		}
		ESP_LOGD(tag, "_valid=%d", dev->_page[dstIndex]._valid);
		if (dev->_page[dstIndex]._valid) (*func)(dev, dstIndex, 0, dev->_page[dstIndex]._segs, dev->_page[srcIndex]._segLen);
		if (srcIndex == dev->_scStart) break;
		srcIndex = srcIndex - dev->_scDirection;
	}
	
	int _text_len = text_len;
	if (_text_len > 16) _text_len = 16;
	
	uint8_t seg = 0;
	uint8_t image[8];
	for (uint8_t i = 0; i < _text_len; i++) {
		memcpy(image, font8x8_basic_tr[(uint8_t)text[i]], 8);
		if (invert) ssd1306_invert(image, 8);
		if (dev->_flip) ssd1306_flip(image, 8);
		(*func)(dev, srcIndex, seg, image, 8);
		for(int j=0;j<8;j++) dev->_page[srcIndex]._segs[seg+j] = image[j];
		seg = seg + 8;
	}
	dev->_page[srcIndex]._valid = true;
	dev->_page[srcIndex]._segLen = seg;
}

void ssd1306_scroll_clear(SSD1306_t * dev)
{
	ESP_LOGD(tag, "dev->_scEnable=%d", dev->_scEnable);
	if (dev->_scEnable == false) return;

	int srcIndex = dev->_scEnd - dev->_scDirection;
	while(1) {
		int dstIndex = srcIndex + dev->_scDirection;
		ESP_LOGD(tag, "srcIndex=%d dstIndex=%d", srcIndex,dstIndex);
		ssd1306_clear_line(dev, dstIndex, false);
		dev->_page[dstIndex]._valid = false;
		if (dstIndex == dev->_scStart) break;
		srcIndex = srcIndex - dev->_scDirection;
	}
}


void ssd1306_hardware_scroll(SSD1306_t * dev, ssd1306_scroll_type_t scroll)
{
	if (dev->_address == SPIAddress) {
		spi_hardware_scroll(dev, scroll);
	} else {
		i2c_hardware_scroll(dev, scroll);
	}
}

void ssd1306_invert(uint8_t *buf, size_t blen)
{
	uint8_t wk;
	for(int i=0; i<blen; i++){
		wk = buf[i];
		buf[i] = ~wk;
	}
}

// Flip upside down
void ssd1306_flip(uint8_t *buf, size_t blen)
{
	for(int i=0; i<blen; i++){
		buf[i] = ssd1306_rotate(buf[i]);
	}
}

// Rotate 8-bit data
// 0x12-->0x48
uint8_t ssd1306_rotate(uint8_t ch1) {
	uint8_t ch2 = 0;
	for (int j=0;j<8;j++) {
		ch2 = (ch2 << 1) + (ch1 & 0x01);
		ch1 = ch1 >> 1;
	}
	return ch2;
}


void ssd1306_fadeout(SSD1306_t * dev)
{
	void (*func)(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
	if (dev->_address == SPIAddress) {
		func = spi_display_image;
	} else {
		func = i2c_display_image;
	}

	uint8_t image[1];
	for(int page=0; page<dev->_pages; page++) {
		image[0] = 0xFF;
		for(int line=0; line<8; line++) {
			if (dev->_flip) {
				image[0] = image[0] >> 1;
			} else {
				image[0] = image[0] << 1;
			}
			for(int seg=0; seg<128; seg++) {
				(*func)(dev, page, seg, image, 1);
			}
		}
	}
}

void ssd1306_dump(SSD1306_t dev)
{
	printf("_address=%x\n",dev._address);
	printf("_width=%x\n",dev._width);
	printf("_height=%x\n",dev._height);
	printf("_pages=%x\n",dev._pages);
}

