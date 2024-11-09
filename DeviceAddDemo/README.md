# DeviceAddDemo for SSD1306

I received a question about using an SSD1306 and other i2c/spi devices at the same time.   
A new i2c driver is now available in ESP-IDF V5.2.   
This complicated the use of other i2c devices at the same time as the i2c's SSD1306.

I will record the results of my investigation and publish sample code.   
If you want to use SSD1306 and other i2c/spi devices at the same time, please follow the guide below.   

If any of the information below is incorrect, please let us know through an issues.

# Using i2c interface

### Use multiple i2c devices on one i2c bus.   
SCL and SDA are shared by all devices.   
```
I2C_NUM_0 --+-- I2C SSD1306
            +---Any I2C Device
```

In the XTENSA series, you can use I2C_NUM_1 bus instead of I2C_NUM_0 bus.
```
I2C_NUM_1 --+-- I2C SSD1306
            +---Any I2C Device
```



#### Legacy driver
Under ESP-IDF V5.2 or later, this project uses the new I2C driver, but there is an option to force the use of the legacy I2C driver.   
SSD1306 and other device use the same frequency.   
__Please note that the maximum i2c clock frequency of SSD1306 is 400KHz.__   
```
I2C_NUM_1 --+-- I2C SSD1306 using 400KHz
            +---Any I2C Device using 400KHz
```

We only need to run this code once.   
No other code is required to use i2c.   
```
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = CONFIG_SDA_GPIO,
        .scl_io_num = CONFIG_SCL_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
```

This project uses the following functions to install the i2c driver.   
This function determines which I2C port to use within the function according to the config value.   
```
i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
```

This project allows you to use an initialization function that does not install the i2c driver.   
This function specifies the I2C port number and I2C address to use as arguments to the function.   
```
i2c_device_add(&dev, i2c_num, CONFIG_RESET_GPIO, I2C_ADDRESS);
```

The i2c driver must be installed before using this initialization function.   
```
    // install i2c master driver
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = CONFIG_SDA_GPIO,
        .scl_io_num = CONFIG_SCL_GPIO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000
    };
    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &i2c_config));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));

    // add SSD1306 to i2c bus
    i2c_device_add(&dev, i2c_num, CONFIG_RESET_GPIO, I2C_ADDRESS);
```

#### New i2c driver
SSD1306 and other devices can use different frequencies.   
This is one of the advantages of the new i2c driver.   
```
I2C_NUM_1 --+-- I2C SSD1306 using 400KHz
            +---Any I2C Device using 100KHz
```

We need to run this code on the first i2c device.   
```
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = scl,
        .sda_io_num = sda,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = I2C_ADDRESS1,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ1,
    };
    i2c_master_dev_handle_t dev_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
```

We need to run this code on the second device.   
```
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = I2C_ADDRESS2,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ2,
    };
    i2c_master_dev_handle_t dev_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
```

This project uses the following functions to install the i2c driver.   
This function determines which I2C port to use within the function according to the config value.   
```
i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
```

This project allows you to use an initialization function that does not install the i2c driver.   
This function specifies the I2C port number and I2C address to use as arguments to the function.   
```
i2c_device_add(&dev, i2c_num, CONFIG_RESET_GPIO, I2C_ADDRESS);
```

The i2c driver must be installed before using this initialization function.   
```
    // install i2c master driver
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = CONFIG_SCL_GPIO,
        .sda_io_num = CONFIG_SDA_GPIO,
        .flags.enable_internal_pullup = true,
    };
    i2c_master_bus_handle_t bus_handle;
    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, &bus_handle));

    // add new device to i2c bus
    dev._i2c_bus_handle = bus_handle;
    i2c_device_add(&dev, i2c_num, CONFIG_RESET_GPIO, I2C_ADDRESS);
```


---

### Use multiple i2c devices on two i2c bus.   
SCL and SDA each use separate GPIOs.   
Install the i2c master driver for each of I2C_NUM_0 and I2C_NUM_1.   
The frequencies of I2C_NUM_0 and I2C_NUM_1 can be set completely independently.   
```
I2C_NUM_0 ----- I2C SSD1306
I2C_NUM_1 ----- Any I2C Device
```

This is possible with both the new i2c driver or the legacy i2c driver, but **both buses must use the same driver.**   
This is not acceptable.   
```
I2C_NUM_0 ----- I2C SSD1306 using new i2c driver
I2C_NUM_1 ----- Any I2C Device using legacy i2c driver
```

If other i2c devices use legacy i2c drivers, SSD1306 must also use legacy i2c drivers.   
Under ESP-IDF V5.2 or later, this project uses the new I2C driver, but there is an option to force the use of the legacy I2C driver.
```
I2C_NUM_0 ----- I2C SSD1306 using legacy i2c driver
I2C_NUM_1 ----- Any I2C Device using legacy i2c driver
```

If SSD1306 use new i2c drivers, other i2c devices must also use new i2c drivers.
```
I2C_NUM_0 ----- I2C SSD1306 using new i2c driver
I2C_NUM_1 ----- Any I2C Device using new i2c driver
```

ESP32C series has only one i2c bus.   
This is not available on the ESP32C series.   
Can only be used with XTENSA series.   

---

# Using spi interface

### Use multiple spi devices on one spi bus.   
MOSI and SCLK are shared by all devices.   
```
SPI2_HOST --+-- SPI SSD1306
            +---Any SPI Device
```

In the XTENSA series, you can use SPI2_HOST bus instead of SPI3_HOST bus.
```
SPI3_HOST --+-- SPI SSD1306
            +---Any SPI Device
```

SSD1306 and other devices can use different frequencies.
```
SPI2_HOST --+-- SPI SSD1306 using 1MHz
            +---Any I2C Device using 2MHz
```

We only need to run this code once.   
No other code is required to use spi.
```
    spi_bus_config_t spi_bus_config = {
        .mosi_io_num = CONFIG_MOSI_GPIO,
        .miso_io_num = -1,
        .sclk_io_num = CONFIG_SCLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
        .flags = 0
    };

    ESP_LOGI(tag, "SPI HOST_ID=%d", host_id);
    esp_err_t ret = spi_bus_initialize( host_id, &spi_bus_config, SPI_DMA_CH_AUTO );
    ESP_LOGI(tag, "spi_bus_initialize=%d",ret);
```

This project uses the following functions to install the spi driver.
```
spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
```

This project allows you to use an initialization function that does not install the spi driver.   
```
spi_device_add(&dev, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
```

The spi driver must be installed before using this initialization function.   
```
    // install spi master driver
    spi_bus_config_t spi_bus_config = {
        .mosi_io_num = CONFIG_MOSI_GPIO,
        .miso_io_num = -1,
        .sclk_io_num = CONFIG_SCLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 0,
        .flags = 0
    };

    esp_err_t ret = spi_bus_initialize( SPI2_HOST, &spi_bus_config, SPI_DMA_CH_AUTO );
    ESP_LOGI(tag, "spi_bus_initialize=%d",ret);
    assert(ret==ESP_OK);

    // add SSD1306 to spi bus
    spi_device_add(&dev, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
```

### Use multiple spi devices on two spi bus.   
MOSI and SCLK each use separate GPIOs.   
Install the spi master driver for each of SPI2_HOST and SPI3_HOST.   
```
SPI2_HOST ----- SPI SSD1306
SPI3_HOST ----- Any SPI Device
```

ESP32C series has only one spi bus.   
This is not available on the ESP32C series.   
Can only be used with XTENSA series.   

