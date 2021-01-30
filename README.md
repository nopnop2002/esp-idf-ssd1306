# esp-idf-ssd1306
SSD1306/SH1106 driver for esp-idf

I used [this](https://github.com/yanbe/ssd1306-esp-idf-i2c) repository as a reference.   
I used [this](https://github.com/dhepper/font8x8) font file.   

# Installation for ESP32

```
git clone https://github.com/nopnop2002/esp-idf-ssd1306
cd esp-idf-ssd1306/
idf.py set-target esp32
idf.py menuconfig
idf.py flash
```

# Installation for ESP32-S2

```
git clone https://github.com/nopnop2002/esp-idf-ssd1306
cd esp-idf-ssd1306/
idf.py set-target esp32s2
idf.py menuconfig
idf.py flash
```

You have to set this config value with menuconfig.   
- CONFIG_INTERFACE   
- CONFIG_PANEL   
- CONFIG_OFFSETXL   
- CONFIG_SDA_GPIO   
- CONFIG_SCL_GPIO   
- CONFIG_RESET_GPIO   
- CONFIG_MOSI_GPIO   
- CONFIG_SCLK_GPIO   
- CONFIG_CS_GPIO   
- CONFIG_DC_GPIO   


![config-main](https://user-images.githubusercontent.com/6020549/101276030-7387f980-37ed-11eb-85af-3babe939f0a1.jpg)

---

# Generic SSD1306 128x32 i2c

![128x32](https://user-images.githubusercontent.com/6020549/56449097-6d12e880-6350-11e9-8edd-7a8fc5eaeedc.JPG)
![config-128x32_i2c](https://user-images.githubusercontent.com/6020549/106342620-04a6b880-62e5-11eb-927d-f933c783d1a1.jpg)

---

# Generic SSD1306 128x64 i2c

![128x64](https://user-images.githubusercontent.com/6020549/56449101-7dc35e80-6350-11e9-8579-32fff38369c0.JPG)
![config-128x64_i2c](https://user-images.githubusercontent.com/6020549/106342623-08d2d600-62e5-11eb-888c-a8784e6c2f3f.jpg)

---

# Generic SH1106 128x64 i2c
__Hardware scroll Not support__   
Left:1.3 inch SH1106   
Right:0.96 inch SSD1303   

![SH1106_i2c](https://user-images.githubusercontent.com/6020549/106342871-09b83780-62e6-11eb-999c-912f0e0c9f0f.JPG)
![config-sh1106_i2c](https://user-images.githubusercontent.com/6020549/106342655-2738d180-62e5-11eb-8be8-90466bbbba63.jpg)

---

# 128x64 TTGO i2c

![ESP32-TTGO-1](https://user-images.githubusercontent.com/6020549/56449111-9764a600-6350-11e9-9902-e2ad1c4aefb0.JPG)
![ESP32-TTGO-2](https://user-images.githubusercontent.com/6020549/56449116-9a5f9680-6350-11e9-86ec-e06648118add.JPG)
![128x64_Reset](https://user-images.githubusercontent.com/6020549/56449118-9e8bb400-6350-11e9-9b90-1eb1f9fa8e99.JPG)
![config-128x64_TTGO](https://user-images.githubusercontent.com/6020549/106342639-18521f00-62e5-11eb-8afa-126cd781eb0e.jpg)

---

# 128x64 ESP-WROOM-32 i2c

![ESP32-OLED-2](https://user-images.githubusercontent.com/6020549/57063327-d229ef00-6cfd-11e9-98ab-8448e14d81e2.JPG)
![config-ESP-WROOM-32](https://user-images.githubusercontent.com/6020549/106342643-1c7e3c80-62e5-11eb-9764-6d820513733d.jpg)

---

# Generic SSD1306 128x32 SPI

![128x32_spi](https://user-images.githubusercontent.com/6020549/106338743-ef775d00-62d7-11eb-8e0c-42c09e6045b9.JPG)
![config-128x32_spi](https://user-images.githubusercontent.com/6020549/106342629-0c665d00-62e5-11eb-8f91-436a9bbc6e63.jpg)

---

# Generic SSD1306 128x64 SPI
D0 is SCLK.    
D1 is MOSI.    

![128x64_spi](https://user-images.githubusercontent.com/6020549/56844607-ee88ee80-68ed-11e9-9b20-ab5e7e0d2a99.JPG)
![config-128x64_spi](https://user-images.githubusercontent.com/6020549/106342634-125c3e00-62e5-11eb-83aa-45fdf5420d4c.jpg)

---

# Generic SH1106 128x64 SPI
__Hardware scroll Not support__   
Left:1.3 inch SH1106   
Right:0.96 inch SSD1303   

![SH1106_spi](https://user-images.githubusercontent.com/6020549/106343561-58b39c00-62e9-11eb-8ce7-913bf15cb803.JPG)
![config-128x32_spi](https://user-images.githubusercontent.com/6020549/106342629-0c665d00-62e5-11eb-8f91-436a9bbc6e63.jpg)

