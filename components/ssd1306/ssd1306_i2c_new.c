#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/i2c_master.h"
#include "esp_log.h"

#include "ssd1306.h"

#define TAG "SSD1306"

#if CONFIG_I2C_PORT_0
#define I2C_NUM I2C_NUM_0
#elif CONFIG_I2C_PORT_1
#define I2C_NUM I2C_NUM_1
#else
#define I2C_NUM I2C_NUM_0 // if spi is selected
#endif

#define I2C_MASTER_FREQ_HZ 400000 // I2C clock of SSD1306 can run at 400 kHz max.
#define I2C_TICKS_TO_WAIT 100     // Maximum ticks to wait before issuing a timeout.

i2c_master_dev_handle_t dev_handle;

void i2c_master_init(SSD1306_t * dev, int16_t sda, int16_t scl, int16_t reset)
{
	ESP_LOGI(TAG, "New i2c driver is used");
	i2c_master_bus_config_t i2c_mst_config = {
		.clk_source = I2C_CLK_SRC_DEFAULT,
		.glitch_ignore_cnt = 7,
		.i2c_port = I2C_NUM,
		.scl_io_num = scl,
		.sda_io_num = sda,
		.flags.enable_internal_pullup = true,
	};
	i2c_master_bus_handle_t bus_handle;
	ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

	i2c_device_config_t dev_cfg = {
		.dev_addr_length = I2C_ADDR_BIT_LEN_7,
		.device_address = I2C_ADDRESS,
		.scl_speed_hz = I2C_MASTER_FREQ_HZ,
	};
	//i2c_master_dev_handle_t dev_handle;
	ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));

#if 0
	i2c_config_t i2c_config = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = sda,
		.scl_io_num = scl,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = I2C_MASTER_FREQ_HZ
	};
	ESP_ERROR_CHECK(i2c_param_config(I2C_NUM, &i2c_config));
	ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM, I2C_MODE_MASTER, 0, 0, 0));
#endif

	if (reset >= 0) {
		//gpio_pad_select_gpio(reset);
		gpio_reset_pin(reset);
		gpio_set_direction(reset, GPIO_MODE_OUTPUT);
		gpio_set_level(reset, 0);
		vTaskDelay(50 / portTICK_PERIOD_MS);
		gpio_set_level(reset, 1);
	}
	dev->_address = I2C_ADDRESS;
	dev->_flip = false;
}

void i2c_init(SSD1306_t * dev, int width, int height) {
	dev->_width = width;
	dev->_height = height;
	dev->_pages = 8;
	if (dev->_height == 32) dev->_pages = 4;
	
	uint8_t out_buf[27];
	int out_index = 0;
	out_buf[out_index++] = OLED_CONTROL_BYTE_CMD_STREAM;
	out_buf[out_index++] = OLED_CMD_DISPLAY_OFF;	            // AE
	out_buf[out_index++] = OLED_CMD_SET_MUX_RATIO;           // A8
	if (dev->_height == 64) out_buf[out_index++] = 0x3F;
	if (dev->_height == 32) out_buf[out_index++] = 0x1F;
	out_buf[out_index++] = OLED_CMD_SET_DISPLAY_OFFSET;      // D3
	out_buf[out_index++] = 0x00;
	//out_buf[out_index++] = OLED_CONTROL_BYTE_DATA_STREAM;	// 40
	out_buf[out_index++] = OLED_CMD_SET_DISPLAY_START_LINE;	// 40
	//out_buf[out_index++] = OLED_CMD_SET_SEGMENT_REMAP;		// A1
	if (dev->_flip) {
		out_buf[out_index++] = OLED_CMD_SET_SEGMENT_REMAP_0; // A0
	} else {
		out_buf[out_index++] = OLED_CMD_SET_SEGMENT_REMAP_1;	// A1
	}
	out_buf[out_index++] = OLED_CMD_SET_COM_SCAN_MODE;		// C8
	out_buf[out_index++] = OLED_CMD_SET_DISPLAY_CLK_DIV;		// D5
	out_buf[out_index++] = 0x80;
	out_buf[out_index++] = OLED_CMD_SET_COM_PIN_MAP;			// DA
	if (dev->_height == 64) out_buf[out_index++] = 0x12;
	if (dev->_height == 32) out_buf[out_index++] = 0x02;
	out_buf[out_index++] = OLED_CMD_SET_CONTRAST;			// 81
	out_buf[out_index++] = 0xFF;
	out_buf[out_index++] = OLED_CMD_DISPLAY_RAM;				// A4
	out_buf[out_index++] = OLED_CMD_SET_VCOMH_DESELCT;		// DB
	out_buf[out_index++] = 0x40;
	out_buf[out_index++] = OLED_CMD_SET_MEMORY_ADDR_MODE;	// 20
	//out_buf[out_index++] = OLED_CMD_SET_HORI_ADDR_MODE;	// 00
	out_buf[out_index++] = OLED_CMD_SET_PAGE_ADDR_MODE;		// 02
	// Set Lower Column Start Address for Page Addressing Mode
	out_buf[out_index++] = 0x00;
	// Set Higher Column Start Address for Page Addressing Mode
	out_buf[out_index++] = 0x10;
	out_buf[out_index++] = OLED_CMD_SET_CHARGE_PUMP;			// 8D
	out_buf[out_index++] = 0x14;
	out_buf[out_index++] = OLED_CMD_DEACTIVE_SCROLL;			// 2E
	out_buf[out_index++] = OLED_CMD_DISPLAY_NORMAL;			// A6
	out_buf[out_index++] = OLED_CMD_DISPLAY_ON;				// AF

	esp_err_t res;
	res = i2c_master_transmit(dev_handle, out_buf, out_index, I2C_TICKS_TO_WAIT);
	if (res == ESP_OK) {
		ESP_LOGI(TAG, "OLED configured successfully");
	} else {
		ESP_LOGE(TAG, "Could not write to device [0x%02x at %d]: %d (%s)", dev->_address, I2C_NUM, res, esp_err_to_name(res));
	}
}


void i2c_display_image(SSD1306_t * dev, int page, int seg, uint8_t * images, int width) {
	if (page >= dev->_pages) return;
	if (seg >= dev->_width) return;

	int _seg = seg + CONFIG_OFFSETX;
	uint8_t columLow = _seg & 0x0F;
	uint8_t columHigh = (_seg >> 4) & 0x0F;

	int _page = page;
	if (dev->_flip) {
		_page = (dev->_pages - page) - 1;
	}

	uint8_t *out_buf;
	out_buf = malloc(width + 1);
	if (out_buf == NULL) {
		ESP_LOGE(TAG, "malloc fail");
		return;
	}
	int out_index = 0;
	out_buf[out_index++] = OLED_CONTROL_BYTE_CMD_STREAM;
	// Set Lower Column Start Address for Page Addressing Mode
	out_buf[out_index++] = (0x00 + columLow);
	// Set Higher Column Start Address for Page Addressing Mode
	out_buf[out_index++] = (0x10 + columHigh);
	// Set Page Start Address for Page Addressing Mode
	out_buf[out_index++] = 0xB0 | _page;

	esp_err_t res;
	res = i2c_master_transmit(dev_handle, out_buf, out_index, I2C_TICKS_TO_WAIT);
	if (res != ESP_OK)
		ESP_LOGE(TAG, "Could not write to device [0x%02x at %d]: %d (%s)", dev->_address, I2C_NUM, res, esp_err_to_name(res));

	out_buf[0] = OLED_CONTROL_BYTE_DATA_STREAM;
	memcpy(&out_buf[1], images, width);

	res = i2c_master_transmit(dev_handle, out_buf, width + 1, I2C_TICKS_TO_WAIT);
	if (res != ESP_OK)
		ESP_LOGE(TAG, "Could not write to device [0x%02x at %d]: %d (%s)", dev->_address, I2C_NUM, res, esp_err_to_name(res));
	free(out_buf);
}

void i2c_contrast(SSD1306_t * dev, int contrast) {
	uint8_t _contrast = contrast;
	if (contrast < 0x0) _contrast = 0;
	if (contrast > 0xFF) _contrast = 0xFF;

	uint8_t out_buf[3];
	int out_index = 0;
	out_buf[out_index++] = OLED_CONTROL_BYTE_CMD_STREAM; // 00
	out_buf[out_index++] = OLED_CMD_SET_CONTRAST; // 81
	out_buf[out_index++] = _contrast;

	esp_err_t res = i2c_master_transmit(dev_handle, out_buf, 3, I2C_TICKS_TO_WAIT);
	if (res != ESP_OK)
		ESP_LOGE(TAG, "Could not write to device [0x%02x at %d]: %d (%s)", dev->_address, I2C_NUM, res, esp_err_to_name(res));
}


void i2c_hardware_scroll(SSD1306_t * dev, ssd1306_scroll_type_t scroll) {
    uint8_t out_buf[11];
    int out_index = 0;
	out_buf[out_index++] = OLED_CONTROL_BYTE_CMD_STREAM; // 00

	if (scroll == SCROLL_RIGHT) {
		out_buf[out_index++] = OLED_CMD_HORIZONTAL_RIGHT; // 26
		out_buf[out_index++] = 0x00; // Dummy byte
		out_buf[out_index++] = 0x00; // Define start page address
		out_buf[out_index++] = 0x07; // Frame frequency
		out_buf[out_index++] = 0x07; // Define end page address
		out_buf[out_index++] = 0x00; //
		out_buf[out_index++] = 0xFF; //
		out_buf[out_index++] = OLED_CMD_ACTIVE_SCROLL; // 2F
	} 

	if (scroll == SCROLL_LEFT) {
		out_buf[out_index++] = OLED_CMD_HORIZONTAL_LEFT; // 27
		out_buf[out_index++] = 0x00; // Dummy byte
		out_buf[out_index++] = 0x00; // Define start page address
		out_buf[out_index++] = 0x07; // Frame frequency
		out_buf[out_index++] = 0x07; // Define end page address
		out_buf[out_index++] = 0x00; //
		out_buf[out_index++] = 0xFF; //
		out_buf[out_index++] = OLED_CMD_ACTIVE_SCROLL; // 2F
	} 

	if (scroll == SCROLL_DOWN) {
		out_buf[out_index++] = OLED_CMD_CONTINUOUS_SCROLL; // 29
		out_buf[out_index++] = 0x00; // Dummy byte
		out_buf[out_index++] = 0x00; // Define start page address
		out_buf[out_index++] = 0x07; // Frame frequency
		//out_buf[out_index++] = 0x01; // Define end page address
		out_buf[out_index++] = 0x00; // Define end page address
		out_buf[out_index++] = 0x3F; // Vertical scrolling offset

		out_buf[out_index++] = OLED_CMD_VERTICAL; // A3
		out_buf[out_index++] = 0x00;
		if (dev->_height == 64)
		//out_buf[out_index++] = 0x7F;
		out_buf[out_index++] = 0x40;
		if (dev->_height == 32)
		out_buf[out_index++] = 0x20;
		out_buf[out_index++] = OLED_CMD_ACTIVE_SCROLL; // 2F
	}

	if (scroll == SCROLL_UP) {
		out_buf[out_index++] = OLED_CMD_CONTINUOUS_SCROLL; // 29
		out_buf[out_index++] = 0x00; // Dummy byte
		out_buf[out_index++] = 0x00; // Define start page address
		out_buf[out_index++] = 0x07; // Frame frequency
		//out_buf[out_index++] = 0x01; // Define end page address
		out_buf[out_index++] = 0x00; // Define end page address
		out_buf[out_index++] = 0x01; // Vertical scrolling offset

		out_buf[out_index++] = OLED_CMD_VERTICAL; // A3
		out_buf[out_index++] = 0x00;
		if (dev->_height == 64)
		//out_buf[out_index++] = 0x7F;
		out_buf[out_index++] = 0x40;
		if (dev->_height == 32)
		out_buf[out_index++] = 0x20;
		out_buf[out_index++] = OLED_CMD_ACTIVE_SCROLL; // 2F
	}

	if (scroll == SCROLL_STOP) {
		out_buf[out_index++] = OLED_CMD_DEACTIVE_SCROLL; // 2E
	}

	esp_err_t res = i2c_master_transmit(dev_handle, out_buf, 3, I2C_TICKS_TO_WAIT);
	if (res != ESP_OK)
		ESP_LOGE(TAG, "Could not write to device [0x%02x at %d]: %d (%s)", dev->_address, I2C_NUM, res, esp_err_to_name(res));
}

