# esp-idf-ssd1306
Example code for driving OLED display with SSD1306 driver using ESP-IDF.   


I used [this](https://github.com/yanbe/ssd1306-esp-idf-i2c) repository as a reference.   
I used [this](https://github.com/dhepper/font8x8) font file.   

You have to set this config value with menuconfig.   
- CONFIG_INTERFACE   
- CONFIG_PANEL   
- CONFIG_SDA_GPIO   
- CONFIG_SCL_GPIO   
- CONFIG_RESET_GPIO   
- CONFIG_CS_GPIO   
- CONFIG_DC_GPIO   

```
git clone https://github.com/nopnop2002/esp-idf-ssd1306
cd esp-idf-ssd1306/
make menuconfig
make flash
```

![config](https://user-images.githubusercontent.com/6020549/56449085-4f458380-6350-11e9-95f8-8583c3f78e80.jpg)

---

# 128x32 i2c

![128x32](https://user-images.githubusercontent.com/6020549/56449097-6d12e880-6350-11e9-8edd-7a8fc5eaeedc.JPG)
![config-128x32_i2c](https://user-images.githubusercontent.com/6020549/58878909-5c0b1480-870f-11e9-90db-20d3d103415b.jpg)

RESET GPIO is not use.   

---

# 128x64 i2c

![128x64](https://user-images.githubusercontent.com/6020549/56449101-7dc35e80-6350-11e9-8579-32fff38369c0.JPG)
![config-128x64_i2c](https://user-images.githubusercontent.com/6020549/58878927-69c09a00-870f-11e9-9dee-72e5647a0004.jpg)

RESET GPIO is not use.   

---

# 128x64 TTGO

![ESP32-TTGO-1](https://user-images.githubusercontent.com/6020549/56449111-9764a600-6350-11e9-9902-e2ad1c4aefb0.JPG)
![ESP32-TTGO-2](https://user-images.githubusercontent.com/6020549/56449116-9a5f9680-6350-11e9-86ec-e06648118add.JPG)
![128x64_Reset](https://user-images.githubusercontent.com/6020549/56449118-9e8bb400-6350-11e9-9b90-1eb1f9fa8e99.JPG)
![config-128x64_TTGO](https://user-images.githubusercontent.com/6020549/58879031-a4c2cd80-870f-11e9-941b-05c6a14e3e9f.jpg)

RESET GPIO is use.   

---

# 128x64 ESP-WROOM-32

![ESP32-OLED-2](https://user-images.githubusercontent.com/6020549/57063327-d229ef00-6cfd-11e9-98ab-8448e14d81e2.JPG)
![config-ESP-WROOM-32](https://user-images.githubusercontent.com/6020549/58879064-b4421680-870f-11e9-94c6-c3008fb56203.jpg)

RESET GPIO is not use.   

---

# 128x64 SPI

![128x64_spi](https://user-images.githubusercontent.com/6020549/56844607-ee88ee80-68ed-11e9-9b20-ab5e7e0d2a99.JPG)
![config-128x64_spi](https://user-images.githubusercontent.com/6020549/58879091-cae86d80-870f-11e9-82da-6e757fbe2f20.jpg)

MOSI(D0) is GPIO13.   
SCLK(D1) is GPIO14.   


