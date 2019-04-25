#ifndef MAIN_SSD1366_H_
#define MAIN_SSD1366_H_

// Following definitions are bollowed from 
// http://robotcantalk.blogspot.com/2015/03/interfacing-arduino-with-ssd1306-driven.html

/* Control byte
Co : bit 8 : Continuation Bit 
 * 1 = no-continuation (only one byte to follow) 
 * 0 = the controller should expect a stream of bytes. 
D/C# : bit 7 : Data/Command Select bit 
 * 1 = the next byte or byte stream will be Data. 
 * 0 = a Command byte or byte stream will be coming up next. 
 Bits 6-0 will be all zeros. 
Usage: 
0x80 : Single Command byte 
0x00 : Command Stream 
0xC0 : Single Data byte 
0x40 : Data Stream
*/
#define OLED_CONTROL_BYTE_CMD_SINGLE    0x80
#define OLED_CONTROL_BYTE_CMD_STREAM    0x00
#define OLED_CONTROL_BYTE_DATA_SINGLE   0xC0
#define OLED_CONTROL_BYTE_DATA_STREAM   0x40

// Fundamental commands (pg.28)
#define OLED_CMD_SET_CONTRAST           0x81    // follow with 0x7F
#define OLED_CMD_DISPLAY_RAM            0xA4
#define OLED_CMD_DISPLAY_ALLON          0xA5
#define OLED_CMD_DISPLAY_NORMAL         0xA6
#define OLED_CMD_DISPLAY_INVERTED       0xA7
#define OLED_CMD_DISPLAY_OFF            0xAE
#define OLED_CMD_DISPLAY_ON             0xAF

// Addressing Command Table (pg.30)
#define OLED_CMD_SET_MEMORY_ADDR_MODE   0x20
#define OLED_CMD_SET_HORI_ADDR_MODE     0x00    // Horizontal Addressing Mode
#define OLED_CMD_SET_VERT_ADDR_MODE     0x01    // Vertical Addressing Mode
#define OLED_CMD_SET_PAGE_ADDR_MODE     0x02    // Page Addressing Mode
#define OLED_CMD_SET_COLUMN_RANGE       0x21    // can be used only in HORZ/VERT mode - follow with 0x00 and 0x7F = COL127
#define OLED_CMD_SET_PAGE_RANGE         0x22    // can be used only in HORZ/VERT mode - follow with 0x00 and 0x07 = PAGE7

// Hardware Config (pg.31)
#define OLED_CMD_SET_DISPLAY_START_LINE 0x40
#define OLED_CMD_SET_SEGMENT_REMAP      0xA1    
#define OLED_CMD_SET_MUX_RATIO          0xA8    // follow with 0x3F = 64 MUX
#define OLED_CMD_SET_COM_SCAN_MODE      0xC8    
#define OLED_CMD_SET_DISPLAY_OFFSET     0xD3    // follow with 0x00
#define OLED_CMD_SET_COM_PIN_MAP        0xDA    // follow with 0x12
#define OLED_CMD_NOP                    0xE3    // NOP

// Timing and Driving Scheme (pg.32)
#define OLED_CMD_SET_DISPLAY_CLK_DIV    0xD5    // follow with 0x80
#define OLED_CMD_SET_PRECHARGE          0xD9    // follow with 0xF1
#define OLED_CMD_SET_VCOMH_DESELCT      0xDB    // follow with 0x30

// Charge Pump (pg.62)
#define OLED_CMD_SET_CHARGE_PUMP        0x8D    // follow with 0x14

// Scrolling Command
#define OLED_CMD_HORIZONTAL_RIGHT       0x26
#define OLED_CMD_HORIZONTAL_LEFT        0x27
#define OLED_CMD_CONTINUOUS_SCROLL      0x29
#define OLED_CMD_DEACTIVE_SCROLL        0x2E
#define OLED_CMD_ACTIVE_SCROLL          0x2F
#define OLED_CMD_VERTICAL		        0xA3

typedef enum {
	SSD1306_128x64 = 1,	// 128x64 panel
	SSD1306_128x32 = 2	// 128x32 panel
} ssd1306_panel_type_t;

typedef enum {
	SCROLL_RIGHT = 1,
	SCROLL_LEFT = 2,
	SCROLL_DOWN = 3,
	SCROLL_UP = 4,
	SCROLL_STOP = 5
} ssd1306_scroll_type_t;

typedef struct {
	uint8_t _segs[128];
} PAGE_t;

typedef struct {
	int _address;
	int _width;
	int _height;
	int _pages;
	PAGE_t _page[8];
} SSD1306_t;

void i2c_master_init(int sda, int scl, int reset);
void ssd1306_init(SSD1306_t * dev, int width, int height, int I2CAddress);
void ssd1306_display_text(SSD1306_t * dev, int page, char * text, int text_len, bool invert);
void ssd1306_display_image(SSD1306_t * dev, int page, int seg, uint8_t * images, int width);
void ssd1306_clear_screen(SSD1306_t * dev, bool invert);
void ssd1306_clear_line(SSD1306_t * dev, int page, bool invert);
void ssd1306_contrast(SSD1306_t dev, int contrast);
void ssd1306_page_up(SSD1306_t * dev);
void ssd1306_page_down(SSD1306_t * dev);
void ssd1306_scroll(SSD1306_t dev, ssd1306_scroll_type_t scroll);
void ssd1306_invert(uint8_t *buf, size_t blen);
void ssd1306_fadeout(SSD1306_t * dev);
void ssd1306_dump(SSD1306_t dev);
#endif /* MAIN_SSD1366_H_ */

