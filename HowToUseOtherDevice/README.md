# How to use other i2c device at same time
I received a question about using an SSD1306 and other i2c devices at the same time.   
A new i2c driver is now available in ESP-IDF V5.2.   
This complicated the use of other i2c devices at the same time as the SSD1306.   

I will record the survey results here.   
If you want to use SSD1306 and other i2c devices at the same time, please follow the guide below.   

## Case 1
Use multiple i2c devices on one i2c bus.   
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

- Legacy driver

We only need to run this code once.   
There is no need to memorize any data.   
SSD1306 and other device use the same frequency.   
Please note that the maximum i2c clock frequency of SSD1306 is 400KHz.   
Under ESP-IDF V5.2 or later, this project uses the new I2C driver, but there is an option to force the use of the legacy I2C driver.

```
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
```

This project uses the following functions to install the i2c driver.
```
i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
```

This project allows you to use an initialization function that does not install the i2c driver.   
The i2c driver must be installed before using this initialization function.   
```
i2c_master_init(&dev, I2C_DRIVER_NOT_INSTALL, I2C_DRIVER_NOT_INSTALL, CONFIG_RESET_GPIO);
```


- New i2c driver

We need to run this code on the first i2c device.   
```
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
        .device_address = I2C_ADDRESS1,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ1,
    };
    i2c_master_dev_handle_t dev_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
```

We need to run this code on the second device.   
SSD1306 ans other device can use different frequencies.   

```
    // We need to load bus_handle from somewhere.

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = I2C_ADDRESS2,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ2,
    };
    i2c_master_dev_handle_t dev_handle;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle));
```

This project uses the following functions to install the i2c driver.
```
i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
```

This project allows you to use an initialization function that does not install the i2c driver.   
```
i2c_device_add(&dev, bus_handle, CONFIG_RESET_GPIO);
```

The i2c driver must be installed before using this initialization function.   
```
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

    i2c_device_add(&dev, bus_handle, CONFIG_RESET_GPIO);
```


---

## Case 2
Use multiple i2c devices on two i2c bus.   
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

