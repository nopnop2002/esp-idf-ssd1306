# esp-idf-ssd1306
SSD1306/SH1106 driver for esp-idf

I used [this](https://github.com/yanbe/ssd1306-esp-idf-i2c) repository as a reference.   
I used [this](https://github.com/dhepper/font8x8) font file.   

# Software requirements
ESP-IDF V5.0 or later.   
ESP-IDF V4.4 release branch reached EOL in July 2024.   

__Note for ESP32C2.__   
ESP-IDF V5.0 ESP32C2 i2c driver has a bug.   
ESP-IDF V5.1 is required when using i2c of ESP32C2.   

__Note for ESP32C6 and ESP32H2.__   
ESP-IDF V5.1 is required when using ESP32C6 and ESP32H2.   

__Note for ESP-IDF V5.2.__   
A new i2c driver is now available in ESP-IDF V5.2.   
Under ESP-IDF V5.2 or later, this project uses a new i2c driver.   

# Installation   

```
git clone https://github.com/nopnop2002/esp-idf-ssd1306
cd esp-idf-ssd1306/TextDemo/
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6/esp32h2}
idf.py menuconfig
idf.py flash
```

__Note for ESP32C3__   
For some reason, there are development boards that cannot use GPIO06, GPIO08, GPIO09, GPIO19 for SPI clock pins.   
According to the ESP32C3 specifications, these pins can also be used as SPI clocks.   
I used a raw ESP-C3-13 to verify that these pins could be used as SPI clocks.   

# Configuration   
You have to set this config value with menuconfig.   
- CONFIG_INTERFACE   
- CONFIG_PANEL   
- CONFIG_OFFSETX   
- CONFIG_FLIP   
- CONFIG_SDA_GPIO   
- CONFIG_SCL_GPIO   
- CONFIG_RESET_GPIO   
- CONFIG_MOSI_GPIO   
- CONFIG_SCLK_GPIO   
- CONFIG_CS_GPIO   
- CONFIG_DC_GPIO   


![config-main](https://user-images.githubusercontent.com/6020549/101276030-7387f980-37ed-11eb-85af-3babe939f0a1.jpg)

# Generic SSD1306 128x32 i2c

![128x32](https://user-images.githubusercontent.com/6020549/56449097-6d12e880-6350-11e9-8edd-7a8fc5eaeedc.JPG)
![config-128x32_i2c](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/9a7e019f-09d3-4c23-8f9c-544847e5f365)

# Generic SSD1306 128x64 i2c

![128x64](https://user-images.githubusercontent.com/6020549/56449101-7dc35e80-6350-11e9-8579-32fff38369c0.JPG)
![config-128x64_i2c](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/794645f9-9f95-4760-8a55-9befceb9349e)

# Generic SH1106 128x64 i2c
Many sellers sell SH1106 as SSD1306.   
__SH1106 does not support hardware scrolling.__   
Left:1.3 inch SH1106   
Right:0.96 inch SSD1306   

![SH1106_i2c](https://user-images.githubusercontent.com/6020549/106342871-09b83780-62e6-11eb-999c-912f0e0c9f0f.JPG)
![config-sh1106_i2c](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/4f4e7638-5519-4a1d-9932-780a4d87a8e6)

# 128x64 TTGO
Unlike other ESP32 development boards, the RTC_CLOCK crystal on this board uses a 26MHz one.   
You need to change the Main XTAL frequency to 26MHz using menuconfig.   

![ESP32-TTGO-1](https://user-images.githubusercontent.com/6020549/56449111-9764a600-6350-11e9-9902-e2ad1c4aefb0.JPG)
![ESP32-TTGO-2](https://user-images.githubusercontent.com/6020549/56449116-9a5f9680-6350-11e9-86ec-e06648118add.JPG)
![128x64_Reset](https://user-images.githubusercontent.com/6020549/56449118-9e8bb400-6350-11e9-9b90-1eb1f9fa8e99.JPG)
![config-128x64_TTGO](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/f234b8e0-ef4e-49db-ad78-bbc705649a18)
![config-128x64_TTGO-2](https://github.com/user-attachments/assets/8744f2bc-704a-4385-9a97-4df612a2ef4e)

# 128x64 ESP-WROOM-32

![ESP32-OLED-2](https://user-images.githubusercontent.com/6020549/57063327-d229ef00-6cfd-11e9-98ab-8448e14d81e2.JPG)
![config-ESP-WROOM-32](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/72434f83-8496-43bb-9333-8c35db155c74)

# Generic SSD1306 128x32 SPI

![128x32_spi](https://user-images.githubusercontent.com/6020549/106338743-ef775d00-62d7-11eb-8e0c-42c09e6045b9.JPG)
![config-128x32_spi](https://user-images.githubusercontent.com/6020549/202815621-f9d0d2c8-3b72-41bb-bf2e-59f984177f03.jpg)


# Generic SSD1306 128x64 SPI
D0 is SCLK.    
D1 is MOSI.    

![128x64_spi](https://user-images.githubusercontent.com/6020549/56844607-ee88ee80-68ed-11e9-9b20-ab5e7e0d2a99.JPG)
![config-128x64_spi](https://user-images.githubusercontent.com/6020549/202815721-189f9abe-7195-43de-b1c9-b4d1fd40af86.jpg)


# Generic SH1106 128x64 SPI
Many sellers sell SH1106 as SSD1306.   
__SH1106 does not support hardware scrolling.__   
Left:1.3 inch SH1106   
Right:0.96 inch SSD1306   

![SH1106_spi](https://user-images.githubusercontent.com/6020549/106343561-58b39c00-62e9-11eb-8ce7-913bf15cb803.JPG)
![config-sh1106_spi](https://user-images.githubusercontent.com/6020549/202815762-f2431f59-8d21-4b9b-a822-330cb2bc9afd.jpg)


# I2C Clock speed   
According to the SSD1306 datasheet, the minimum i2c clock cycle time is 2.5us.   
Therefore, the maximum i2c clock frequency is 400KHz.   
The i2c clock frequency used by this project is 400KHz.   

# I2C Port selection   
![config-i2c-port](https://github.com/user-attachments/assets/477bdf29-7492-4256-bc9e-e3ff363cddcc)

XTENSA's ESP32 has two i2c port: I2C_NUM_0/1.   
You can use these two ports freely.   
If you use this module at the same time as another I2C device using I2C port 0, you must change it to I2C port 1.   

# Force legacy i2c driver
XTENSA's ESP32 has two i2c port: I2C_NUM_0/1.   
I2C_NUM_0/1 are initialized independently, but legacy i2c drivers and new i2c drivers cannot be mixed.   
If I2C_NUM_0 is initialized with the legacy i2c driver, I2C_NUM_1 must also be initialized with the legacy i2c driver.   
If you use the SSD1306 at the same time as other I2C devices that use legacy I2C drivers, the SSD1306 must also be initialized with the legacy I2C driver.   
Enabling this will use the legacy i2c driver even after ESP-IDF V5.2.   
![config-i2c-driver](https://github.com/user-attachments/assets/d07076d0-1c94-43d1-aa5a-aec810d2f7bc)

# SPI Clock speed   
According to the SSD1306 datasheet, the minimum SPI clock cycle time is 100ns.   
Therefore, the maximum SPI clock frequency is 10MHz.   
The SPI clock frequency used by this project is 1MHz.   
Higher SPI clock frequencies can be specified using ```spi_clock_speed()```.   
When using 10MHz, you need to be careful about the length of the wire cable.   
```
    //int speed = 1000000; // 1MHz
    //int speed = 2000000; // 2MHz
    //int speed = 4000000; // 4MHz
    //int speed = 6000000; // 6MHz
    //int speed = 8000000; // 8MHz
    int speed = 10000000; // 10MHz
    spi_clock_speed(speed);
    spi_master_init(&dev, CONFIG_MOSI_GPIO, CONFIG_SCLK_GPIO, CONFIG_CS_GPIO, CONFIG_DC_GPIO, CONFIG_RESET_GPIO);
```

# SPI BUS selection   
![config-spi-bus](https://user-images.githubusercontent.com/6020549/202815807-6c2df14f-f38e-4032-94fb-da1723607279.jpg)

The ESP32 XTENSA series has three SPI BUSs.   
SPI1_HOST is used for communication with Flash memory.   
You can use SPI2_HOST and SPI3_HOST freely.   
When you use SDSPI(SD Card via SPI), SDSPI uses SPI2_HOST BUS.   
When using this module at the same time as SDSPI or other SPI device using SPI2_HOST, it needs to be changed to SPI3_HOST.   
When you don't use SDSPI, both SPI2_HOST and SPI3_HOST will work.   
Previously it was called HSPI_HOST / VSPI_HOST, but now it is called SPI2_HOST / SPI3_HOST.   


# Flip upside down

![config_flip](https://user-images.githubusercontent.com/6020549/115942179-e3b8c280-a4e3-11eb-9b08-8eb830c9f7f4.jpg)

![ssd1306_flip](https://user-images.githubusercontent.com/6020549/115942191-f0d5b180-a4e3-11eb-879e-e7be89eb3e50.JPG)

# How to use this component in your project   
Create idf_component.yml in the same directory as main.c.   
```
YourProject --+-- CMakeLists.txt
              +-- main --+-- main.c
                         +-- CMakeLists.txt
                         +-- idf_component.yml
```

Contents of idf_component.yml.
```
dependencies:
  nopnop2002/ssd1306:
    path: components/ssd1306/
    git: https://github.com/nopnop2002/esp-idf-ssd1306.git
```

When you build a projects esp-idf will automaticly fetch repository to managed_components dir and link with your code.   
```
YourProject --+-- CMakeLists.txt
              +-- main --+-- main.c
              |          +-- CMakeLists.txt
              |          +-- idf_component.yml
              +-- managed_components ----- nopnop2002__ssd1306
```


