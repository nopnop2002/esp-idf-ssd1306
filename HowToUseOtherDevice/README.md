# How to use other i2c devive at same time
I received a question about using an SSD1306 and other i2c devices at the same time.   
Therefore, I will record the survey results here.   
If you want to use SSD1306 and other i2c devices at the same time, please follow the guide below.   

## Case 1
Use multiple i2c devices on one i2c bus.   
SCL and SDA are shared by all devices.   
```
I2C_NUM_0 --+-- I2C SSD1306
            +---Any I2C Device
```

- Legacy driver

We only need to run this code once.   
There is no need to memorize any data.   
SSD1306 and other device use the same frequency.   
Please note that the maximum i2c clock frequency of SSD1306 is 400KHz.   
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


- New i2c driver

We need to run this code on the first i2c device.   
**We need to record bus_handle somewhere.**   
But In different libraries, there is no place to record bus_handle.   
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

    // We need to record bus_handle somewhere.
```

We need to run this code on the second device.   
**We need to load bus_handle from somewhere.**   
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

**This library does not have the function to record bus_handle somewhere or retrieve bus_handle from somewhere.**

---

## Case 2
Use multiple i2c devices on two i2c bus.   
SCL and SDA each use separate GPIOs.   
Install the i2c master driver for each of I2C_NUM_0 and I2C_NUM_1.   
```
I2C_NUM_0 ----- I2C SSD1306
I2C_NUM_1 ----- Any I2C Device
```

This is possible with either the new i2c driver or the legacy i2c driver.   
This is the only way to use new i2c driver.   
ESP32C series has only one i2c bus.   
This is not available on the ESP32C series.   
Can only be used with XTENSA series.   

