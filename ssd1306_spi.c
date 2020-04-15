#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <driver/spi_master.h>
#include <driver/gpio.h>
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

#define tag "SSD1306"

static const int GPIO_MOSI = 13;
static const int GPIO_SCLK = 14;

static const int SPI_Command_Mode = 0;
static const int SPI_Data_Mode = 1;
static const int SPI_Frequency = 1000000;

void spi_master_init(SSD1306_t * dev, int GPIO_CS, int GPIO_DC, int GPIO_RESET)
{
	esp_err_t ret;

	gpio_pad_select_gpio( GPIO_CS );
	gpio_set_direction( GPIO_CS, GPIO_MODE_OUTPUT );
	gpio_set_level( GPIO_CS, 0 );

	gpio_pad_select_gpio( GPIO_DC );
	gpio_set_direction( GPIO_DC, GPIO_MODE_OUTPUT );
	gpio_set_level( GPIO_DC, 0 );

	if ( GPIO_RESET >= 0 ) {
		gpio_pad_select_gpio( GPIO_RESET );
		gpio_set_direction( GPIO_RESET, GPIO_MODE_OUTPUT );
		gpio_set_level( GPIO_RESET, 0 );
		vTaskDelay( pdMS_TO_TICKS( 100 ) );
		gpio_set_level( GPIO_RESET, 1 );
	}

	spi_bus_config_t spi_bus_config = {
		.sclk_io_num = GPIO_SCLK,
		.mosi_io_num = GPIO_MOSI,
		.miso_io_num = -1,
		.quadwp_io_num = -1,
		.quadhd_io_num = -1
	};

	ret = spi_bus_initialize( HSPI_HOST, &spi_bus_config, 1 );
	ESP_LOGI(tag, "spi_bus_initialize=%d",ret);
	assert(ret==ESP_OK);

	spi_device_interface_config_t devcfg;
	memset( &devcfg, 0, sizeof( spi_device_interface_config_t ) );
	devcfg.clock_speed_hz = SPI_Frequency;
	devcfg.spics_io_num = GPIO_CS;
	devcfg.queue_size = 1;

	spi_device_handle_t handle;
	ret = spi_bus_add_device( HSPI_HOST, &devcfg, &handle);
	ESP_LOGI(tag, "spi_bus_add_device=%d",ret);
	assert(ret==ESP_OK);
	dev->_dc = GPIO_DC;
	dev->_SPIHandle = handle;
}


bool spi_master_write_byte(spi_device_handle_t SPIHandle, const uint8_t* Data, size_t DataLength )
{
	spi_transaction_t SPITransaction;

	if ( DataLength > 0 ) {
		memset( &SPITransaction, 0, sizeof( spi_transaction_t ) );
		SPITransaction.length = DataLength * 8;
		SPITransaction.tx_buffer = Data;
		spi_device_transmit( SPIHandle, &SPITransaction );
	}

	return true;
}

bool spi_master_write_command(SSD1306_t * dev, uint8_t Command )
{
	static uint8_t CommandByte = 0;
	CommandByte = Command;
	gpio_set_level( dev->_dc, SPI_Command_Mode );
	return spi_master_write_byte( dev->_SPIHandle, &CommandByte, 1 );
}

bool spi_master_write_data(SSD1306_t * dev, const uint8_t* Data, size_t DataLength )
{
	gpio_set_level( dev->_dc, SPI_Data_Mode );
	return spi_master_write_byte( dev->_SPIHandle, Data, DataLength );
}


void spi_init(SSD1306_t * dev, int width, int height)
{
	dev->_address = SPIAddress;
	dev->_width = width;
	dev->_height = height;
	dev->_pages = 8;
	if (dev->_height == 32) dev->_pages = 4;

	spi_master_write_command(dev, OLED_CMD_DISPLAY_OFF);		// AE
	spi_master_write_command(dev, OLED_CMD_SET_MUX_RATIO);		// A8
	if (dev->_height == 64) spi_master_write_command(dev, 0x3F);
	if (dev->_height == 32) spi_master_write_command(dev, 0x1F);
	spi_master_write_command(dev, OLED_CMD_SET_DISPLAY_OFFSET);	// D3
	spi_master_write_command(dev, 0x00);
	spi_master_write_command(dev, OLED_CONTROL_BYTE_DATA_STREAM);	// 40
	spi_master_write_command(dev, OLED_CMD_SET_SEGMENT_REMAP);	// A1
	spi_master_write_command(dev, OLED_CMD_SET_COM_SCAN_MODE);	// C8
	spi_master_write_command(dev, OLED_CMD_DISPLAY_NORMAL);		// A6
	spi_master_write_command(dev, OLED_CMD_SET_DISPLAY_CLK_DIV);	// D5
	spi_master_write_command(dev, 0x80);
	spi_master_write_command(dev, OLED_CMD_SET_COM_PIN_MAP);	// DA
	if (dev->_height == 64) spi_master_write_command(dev, 0x12);
	if (dev->_height == 32) spi_master_write_command(dev, 0x02);
	spi_master_write_command(dev, OLED_CMD_SET_CONTRAST);		// 81
	spi_master_write_command(dev, 0xFF);
	spi_master_write_command(dev, OLED_CMD_DISPLAY_RAM);		// A4
	spi_master_write_command(dev, OLED_CMD_SET_VCOMH_DESELCT);	// DB
	spi_master_write_command(dev, 0x40);
	spi_master_write_command(dev, OLED_CMD_SET_MEMORY_ADDR_MODE);	// 20
	//spi_master_write_command(dev, OLED_CMD_SET_HORI_ADDR_MODE);	// 00
	spi_master_write_command(dev, OLED_CMD_SET_PAGE_ADDR_MODE);	// 02
	// Set Lower Column Start Address for Page Addressing Mode
	spi_master_write_command(dev, 0x00);
	// Set Higher Column Start Address for Page Addressing Mode
	spi_master_write_command(dev, 0x10);
	spi_master_write_command(dev, OLED_CMD_SET_CHARGE_PUMP);	// 8D
	spi_master_write_command(dev, 0x14);
	spi_master_write_command(dev, OLED_CMD_DEACTIVE_SCROLL);	// 2E
	spi_master_write_command(dev, OLED_CMD_DISPLAY_NORMAL);		// A6
	spi_master_write_command(dev, OLED_CMD_DISPLAY_ON);		// AF
}

void spi_display_text(SSD1306_t * dev, int page, char * text, int text_len, bool invert)
{
	if (page >= dev->_pages) return;
	int _text_len = text_len;
	if (_text_len > 16) _text_len = 16;

	uint8_t seg = 0;
	uint8_t image[8];
	for (uint8_t i = 0; i < _text_len; i++) {
		memcpy(image, font8x8_basic_tr[(uint8_t)text[i]], 8);
		if (invert) ssd1306_invert(image, 8);
		spi_display_image(dev, page, seg, image, 8);
#if 0
		for(int j=0;j<8;j++) 
			dev->_page[page]._segs[seg+j] = image[j];
#endif
		seg = seg + 8;
	}
}

void spi_display_image(SSD1306_t * dev, int page, int seg, uint8_t * images, int width)
{
	if (page >= dev->_pages) return;
	if (seg >= dev->_width) return;

	uint8_t columLow = seg & 0x0F;
	uint8_t columHigh = (seg >> 4) & 0x0F;

	// Set Lower Column Start Address for Page Addressing Mode
	//i2c_master_write_byte(cmd, 0x00, true);
	spi_master_write_command(dev, (0x00 + columLow));
	// Set Higher Column Start Address for Page Addressing Mode
	//spi_master_write_command(dev, 0x10, 1);
	spi_master_write_command(dev, (0x10 + columHigh));
	// Set Page Start Address for Page Addressing Mode
	spi_master_write_command(dev, 0xB0 | page);

	spi_master_write_data(dev, images, width);

}

void spi_contrast(SSD1306_t * dev, int contrast) {
	int _contrast = contrast;
	if (contrast < 0x0) _contrast = 0;
	if (contrast > 0xFF) _contrast = 0xFF;

	spi_master_write_command(dev, OLED_CMD_SET_CONTRAST);			// 81
	spi_master_write_command(dev, _contrast);
}

void spi_hardware_scroll(SSD1306_t * dev, ssd1306_scroll_type_t scroll)
{

	if (scroll == SCROLL_RIGHT) {
		spi_master_write_command(dev, OLED_CMD_HORIZONTAL_RIGHT);	// 26
		spi_master_write_command(dev, 0x00); // Dummy byte
		spi_master_write_command(dev, 0x00); // Define start page address
		spi_master_write_command(dev, 0x07); // Frame frequency
		spi_master_write_command(dev, 0x07); // Define end page address
		spi_master_write_command(dev, 0x00); //
		spi_master_write_command(dev, 0xFF); //
		spi_master_write_command(dev, OLED_CMD_ACTIVE_SCROLL);		// 2F
	} 

	if (scroll == SCROLL_LEFT) {
		spi_master_write_command(dev, OLED_CMD_HORIZONTAL_LEFT);	// 27
		spi_master_write_command(dev, 0x00); // Dummy byte
		spi_master_write_command(dev, 0x00); // Define start page address
		spi_master_write_command(dev, 0x07); // Frame frequency
		spi_master_write_command(dev, 0x07); // Define end page address
		spi_master_write_command(dev, 0x00); //
		spi_master_write_command(dev, 0xFF); //
		spi_master_write_command(dev, OLED_CMD_ACTIVE_SCROLL);		// 2F
	} 

	if (scroll == SCROLL_DOWN) {
		spi_master_write_command(dev, OLED_CMD_CONTINUOUS_SCROLL);	// 29
		spi_master_write_command(dev, 0x00); // Dummy byte
		spi_master_write_command(dev, 0x00); // Define start page address
		spi_master_write_command(dev, 0x07); // Frame frequency
		//spi_master_write_command(dev, 0x01); // Define end page address
		spi_master_write_command(dev, 0x00); // Define end page address
		spi_master_write_command(dev, 0x3F); // Vertical scrolling offset

		spi_master_write_command(dev, OLED_CMD_VERTICAL);		// A3
		spi_master_write_command(dev, 0x00);
		if (dev->_height == 64)
			spi_master_write_command(dev, 0x40);
		if (dev->_height == 32)
			spi_master_write_command(dev, 0x20);
		spi_master_write_command(dev, OLED_CMD_ACTIVE_SCROLL);		// 2F
	}

	if (scroll == SCROLL_UP) {
		spi_master_write_command(dev, OLED_CMD_CONTINUOUS_SCROLL);	// 29
		spi_master_write_command(dev, 0x00); // Dummy byte
		spi_master_write_command(dev, 0x00); // Define start page address
		spi_master_write_command(dev, 0x07); // Frame frequency
		//spi_master_write_command(dev, 0x01); // Define end page address
		spi_master_write_command(dev, 0x00); // Define end page address
		spi_master_write_command(dev, 0x01); // Vertical scrolling offset

		spi_master_write_command(dev, OLED_CMD_VERTICAL);		// A3
		spi_master_write_command(dev, 0x00);
		if (dev->_height == 64)
			spi_master_write_command(dev, 0x40);
		if (dev->_height == 32)
			spi_master_write_command(dev, 0x20);
		spi_master_write_command(dev, OLED_CMD_ACTIVE_SCROLL);		// 2F
	}

	if (scroll == SCROLL_STOP) {
		spi_master_write_command(dev, OLED_CMD_DEACTIVE_SCROLL);	// 2E
	}
}
