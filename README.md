# esp-idf-ssd1306
Sample code for driving OLED display with SSD1306 driver using ESP-IDF.   


I used this repository as a reference.   
https://github.com/yanbe/ssd1306-esp-idf-i2c   

I used this font file.   
https://github.com/dhepper/font8x8   

You have to set this config value with menuconfig.   
CONFIG_INTERFACEL   
CONFIG_MODEL   
CONFIG_SDA_GPIO   
CONFIG_SCL_GPIO   
CONFIG_RESET_GPIO   
CONFIG_CS_GPIO   
CONFIG_DC_GPIO   

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
![config-128x32_i2c](https://user-images.githubusercontent.com/6020549/56844597-c5685e00-68ed-11e9-9969-0f7b39434a21.jpg)

RESET GPIO not used.   
CS GPIO not used.   
DC GPIO not used.   

---

# 128x64 i2c

![128x64](https://user-images.githubusercontent.com/6020549/56449101-7dc35e80-6350-11e9-8579-32fff38369c0.JPG)
![config-128x64_i2c](https://user-images.githubusercontent.com/6020549/56844601-d1542000-68ed-11e9-9331-8b478cf53c8c.jpg)

RESET GPIO not used.   
CS GPIO not used.   
DC GPIO not used.   

---

# 128x64 TTGO

![ESP32-TTGO-1](https://user-images.githubusercontent.com/6020549/56449111-9764a600-6350-11e9-9902-e2ad1c4aefb0.JPG)
![ESP32-TTGO-2](https://user-images.githubusercontent.com/6020549/56449116-9a5f9680-6350-11e9-86ec-e06648118add.JPG)
![128x64_Reset](https://user-images.githubusercontent.com/6020549/56449118-9e8bb400-6350-11e9-9b90-1eb1f9fa8e99.JPG)
![config-128x64_TTGO](https://user-images.githubusercontent.com/6020549/56844603-d5803d80-68ed-11e9-9de5-fb475630ca1d.jpg)

CS GPIO not used.   
DC GPIO not used.   

---

# 128x64 ESP-WROOM-32

![ESP32-OLED-2](https://user-images.githubusercontent.com/6020549/57063327-d229ef00-6cfd-11e9-98ab-8448e14d81e2.JPG)
![config-128x64_esp32](https://user-images.githubusercontent.com/6020549/57063338-dc4bed80-6cfd-11e9-90b5-7b3e7ed74c00.jpg)

RESET GPIO not used.   
CS GPIO not used.   
DC GPIO not used.   

---

# 128x64 SPI

![128x64_spi](https://user-images.githubusercontent.com/6020549/56844607-ee88ee80-68ed-11e9-9b20-ab5e7e0d2a99.JPG)
![config-128x64_spi](https://user-images.githubusercontent.com/6020549/56844609-f34da280-68ed-11e9-995e-4aedae207eac.jpg)

MOSI is GPIO13.   
SCLK is GPIO14.   
SSD1306 Model not used.   
SCL GPIO not used.   
SDA GPIO not used.   


