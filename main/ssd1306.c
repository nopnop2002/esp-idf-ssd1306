#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "ssd1306.h"
//#include "font8x8_basic.h"

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

void ssd1306_page_up(SSD1306_t * dev)
{
	void (*func)(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
	if (dev->_address == SPIAddress) {
		func = spi_display_image;
	} else {
		func = i2c_display_image;
	}

	for (int page = 1; page < dev->_pages; page++) {
		for(int seg = 0; seg < dev->_width; seg++) {
			dev->_page[page-1]._segs[seg] = dev->_page[page]._segs[seg];
		}
	}
	memset(dev->_page[dev->_pages-1]._segs, 0, dev->_width);
	for (int page = 0; page < dev->_pages; page++) {
		(*func)(dev, page, 0, dev->_page[page]._segs, dev->_width);
	}

}

void ssd1306_page_down(SSD1306_t * dev)
{
	void (*func)(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
	if (dev->_address == SPIAddress) {
		func = spi_display_image;
	} else {
		func = i2c_display_image;
	}

	for (int page = dev->_pages-1; page > 0; page--) {
		for(int seg = 0; seg < dev->_width; seg++) {
			dev->_page[page]._segs[seg] = dev->_page[page-1]._segs[seg];
		}
	}
	memset(dev->_page[0]._segs, 0, dev->_width);
	for (int page = 0; page < dev->_pages; page++) {
		(*func)(dev, page, 0, dev->_page[page]._segs, dev->_width);
	}
}

void ssd1306_scroll(SSD1306_t * dev, ssd1306_scroll_type_t scroll)
{
	if (dev->_address == SPIAddress) {
		spi_scroll(dev, scroll);
	} else {
		i2c_scroll(dev, scroll);
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

