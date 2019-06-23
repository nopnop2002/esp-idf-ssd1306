#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

#define tag "SSD1306"

void ssd1306_display_text(SSD1306_t * dev, int page, char * text, int text_len, bool invert)
{
	if (dev->_address == SPIAddress) {
		spi_display_text(dev, page, text, text_len, invert);
	} else {
		i2c_display_text(dev, page, text, text_len, invert);
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
	void (*func)(SSD1306_t * dev, int page, char * text, int text_len, bool invert);
	if (dev->_address == SPIAddress) {
		func = spi_display_text;
	} else {
		func = i2c_display_text;
	}

	char zero[128];
	memset(zero, 0, sizeof(zero));
	for (int page = 0; page < dev->_pages; page++) {
		(*func) (dev, page, zero, 128, invert);
	}
	
}

void ssd1306_clear_line(SSD1306_t * dev, int page, bool invert)
{
	void (*func)(SSD1306_t * dev, int page, char * text, int text_len, bool invert);
	if (dev->_address == SPIAddress) {
		func = spi_display_text;
	} else {
		func = i2c_display_text;
	}

	char zero[128];
	memset(zero, 0, sizeof(zero));
	(*func)(dev, page, zero, 128, invert);
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
			image[0] = image[0] << 1;
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

