# esp-idf-ssd1306
SSD1306 driver for esp-idf

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
- CONFIG_SDA_GPIO   
- CONFIG_SCL_GPIO   
- CONFIG_RESET_GPIO   
- CONFIG_MOSI_GPIO   
- CONFIG_SCLK_GPIO   
- CONFIG_CS_GPIO   
- CONFIG_DC_GPIO   


![config-main](https://user-images.githubusercontent.com/6020549/101276030-7387f980-37ed-11eb-85af-3babe939f0a1.jpg)

---

# Generic 128x32 i2c

![128x32](https://user-images.githubusercontent.com/6020549/56449097-6d12e880-6350-11e9-8edd-7a8fc5eaeedc.JPG)
![config-128x32_i2c](https://user-images.githubusercontent.com/6020549/101276039-85699c80-37ed-11eb-8cc5-07426c60e7de.jpg)

---

# Generic 128x64 i2c

![128x64](https://user-images.githubusercontent.com/6020549/56449101-7dc35e80-6350-11e9-8579-32fff38369c0.JPG)
![config-128x64_i2c](https://user-images.githubusercontent.com/6020549/101276050-961a1280-37ed-11eb-8b85-b8e1de585832.jpg)

---

# 128x64 TTGO

![ESP32-TTGO-1](https://user-images.githubusercontent.com/6020549/56449111-9764a600-6350-11e9-9902-e2ad1c4aefb0.JPG)
![ESP32-TTGO-2](https://user-images.githubusercontent.com/6020549/56449116-9a5f9680-6350-11e9-86ec-e06648118add.JPG)
![128x64_Reset](https://user-images.githubusercontent.com/6020549/56449118-9e8bb400-6350-11e9-9b90-1eb1f9fa8e99.JPG)
![config-128x64_TTGO](https://user-images.githubusercontent.com/6020549/101276064-b8139500-37ed-11eb-8e10-59447903cb80.jpg)

---

# 128x64 ESP-WROOM-32

![ESP32-OLED-2](https://user-images.githubusercontent.com/6020549/57063327-d229ef00-6cfd-11e9-98ab-8448e14d81e2.JPG)
![config-ESP-WROOM-32](https://user-images.githubusercontent.com/6020549/101276069-c5c91a80-37ed-11eb-98bf-c32207d3346f.jpg)

---

# Generic 128x64 SPI

![128x64_spi](https://user-images.githubusercontent.com/6020549/56844607-ee88ee80-68ed-11e9-9b20-ab5e7e0d2a99.JPG)
![config-128x64_spi](https://user-images.githubusercontent.com/6020549/101276076-cd88bf00-37ed-11eb-9183-c8b9f4ee4974.jpg)


