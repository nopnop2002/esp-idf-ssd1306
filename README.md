# esp-idf-ssd1306
SSD1306/SH1106 driver for esp-idf

I used [this](https://github.com/yanbe/ssd1306-esp-idf-i2c) repository as a reference.   
I used [this](https://github.com/dhepper/font8x8) font file.   

# Software requirements
esp-idf v4.4 or later.   
This is because this version supports ESP32-C3.   

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

# Installation for ESP32-C3

```
git clone https://github.com/nopnop2002/esp-idf-ssd1306
cd esp-idf-ssd1306/
idf.py set-target esp32c3
idf.py menuconfig
idf.py flash
```

__Note__   
For some reason GPIO06, GPIO08, GPIO09, GPIO19 cannot be used for SPI clock pins on my board.   
I looked at the ESP32-C3 datasheet, but I don't understand why.   
This may be a problem only for my board.   
If you find a solution, please let me know.   

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

---

# Generic SSD1306 128x32 i2c

![128x32](https://user-images.githubusercontent.com/6020549/56449097-6d12e880-6350-11e9-8edd-7a8fc5eaeedc.JPG)
![config-128x32_i2c](https://user-images.githubusercontent.com/6020549/115942099-79a01d80-a4e3-11eb-9274-8746920fca78.jpg)

---

# Generic SSD1306 128x64 i2c

![128x64](https://user-images.githubusercontent.com/6020549/56449101-7dc35e80-6350-11e9-8579-32fff38369c0.JPG)
![config-128x64_i2c](https://user-images.githubusercontent.com/6020549/127076697-385ecafa-ccb7-4511-a862-70a6143930dd.jpg)

---

# Generic SH1106 128x64 i2c
__Hardware scroll Not support__   
Left:1.3 inch SH1106   
Right:0.96 inch SSD1306   

![SH1106_i2c](https://user-images.githubusercontent.com/6020549/106342871-09b83780-62e6-11eb-999c-912f0e0c9f0f.JPG)
![config-sh1106_i2c](https://user-images.githubusercontent.com/6020549/127077379-ad688621-999e-475e-b1fe-c093d7599783.jpg)

---

# 128x64 TTGO
Unlike other ESP32 development boards, the RTC_CLOCK crystal on this board uses a 26MHz one.   
You need to change the RTC CLOCK frequency to 26MHz using menuconfig.   

![ESP32-TTGO-1](https://user-images.githubusercontent.com/6020549/56449111-9764a600-6350-11e9-9902-e2ad1c4aefb0.JPG)
![ESP32-TTGO-2](https://user-images.githubusercontent.com/6020549/56449116-9a5f9680-6350-11e9-86ec-e06648118add.JPG)
![128x64_Reset](https://user-images.githubusercontent.com/6020549/56449118-9e8bb400-6350-11e9-9b90-1eb1f9fa8e99.JPG)
![config-128x64_TTGO](https://user-images.githubusercontent.com/6020549/106342639-18521f00-62e5-11eb-8afa-126cd781eb0e.jpg)

---

# 128x64 ESP-WROOM-32

![ESP32-OLED-2](https://user-images.githubusercontent.com/6020549/57063327-d229ef00-6cfd-11e9-98ab-8448e14d81e2.JPG)
![config-ESP-WROOM-32](https://user-images.githubusercontent.com/6020549/106342643-1c7e3c80-62e5-11eb-9764-6d820513733d.jpg)

---

# Generic SSD1306 128x32 SPI

![128x32_spi](https://user-images.githubusercontent.com/6020549/106338743-ef775d00-62d7-11eb-8e0c-42c09e6045b9.JPG)
![config-128x32_spi](https://user-images.githubusercontent.com/6020549/127077082-7b60e635-e410-4324-b807-c368d03f5b5f.jpg)

---

# Generic SSD1306 128x64 SPI
D0 is SCLK.    
D1 is MOSI.    

![128x64_spi](https://user-images.githubusercontent.com/6020549/56844607-ee88ee80-68ed-11e9-9b20-ab5e7e0d2a99.JPG)
![config-128x64_spi](https://user-images.githubusercontent.com/6020549/127076276-275715c7-afb4-4922-bb93-bd66f232606b.jpg)

---

# Generic SH1106 128x64 SPI
__Hardware scroll Not support__   
Left:1.3 inch SH1106   
Right:0.96 inch SSD1306   

![SH1106_spi](https://user-images.githubusercontent.com/6020549/106343561-58b39c00-62e9-11eb-8ce7-913bf15cb803.JPG)
![config-sh1106_spi](https://user-images.githubusercontent.com/6020549/127077395-d1a9b34c-6000-4aa6-a2e4-13fdbfac6fbb.jpg)

---

# Flip upside down

![config_flip](https://user-images.githubusercontent.com/6020549/115942179-e3b8c280-a4e3-11eb-9b08-8eb830c9f7f4.jpg)

![ssd1306_flip](https://user-images.githubusercontent.com/6020549/115942191-f0d5b180-a4e3-11eb-879e-e7be89eb3e50.JPG)

