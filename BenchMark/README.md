# BenchMark for SSD1306
A new i2c driver is now available in ESP-IDF V5.2.   
The previous i2c driver is still available as a Legacy driver.   
We measured the performance of new i2c drivers, legacy i2c drivers, and SPI drivers.   

# Software requirements
ESP-IDF V4.4/V5.x.   

__Note for new i2c driver__   
ESP-IDF V5.2 is required when using the new i2c driver.   

# Installation
```
git clone https://github.com/nopnop2002/esp-idf-ssd1306
cd esp-idf-ssd1306/BenchMark/
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6/esp32h2}
idf.py menuconfig
idf.py flash
```

# i2c interface benchmark
The maximum i2c clock frequency of SSD1306 is 400KHz.   
The i2c clock frequency used by this project is 400KHz.   
The measurement result is [FPS].   
__Wire cables should be as short as possible.__   
For any SoCs, the New Driver achieved faster results than the Legacy Driver.   
|SoC@CPU Freq|Legacy Driver|New Driver||
|:-:|:-:|:-:|:-:|
|ESP32@160|34.0|35.2||
|ESP32@240|35.4|36.2||
|ESP32S2@160|36.7|37.8||
|ESP32S2@240|38.0|38.6||
|ESP32S3@160|36.1|37.3||
|ESP32S3@240|37.6|38.4||
|ESP32C2@120|36.2|37.1|26MHz XTAL|
|ESP32C3@160|37.0|38.1||
|ESP32C6@160|37.1|38.2||
|ESP32H2@96|34.6|36.4||

ESP32C6 gave the fastest results when the CPU frequency was 160MHz (120MHz or 96MHz for some SoCs).   
The difference between ESP32C6 and ESP32C3 is very small.   
![i2c_160MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/cb641422-3a06-4da4-8776-edd3fe965fc6)

ESP32S2 gave the fastest results when the CPU frequency was 240MHz.   
![i2c_240MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/ebd5e195-0bd1-4791-9293-57dbf50fd13a)

![i2c_legacy](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/44a55206-1622-4a1e-b898-4b673bc465c3)
![i2c_new](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/dad01f46-3497-4312-8d77-9fd1b3d3b782)

# SPI interface benchmark
The maximum SPI clock frequency of SSD1306 is 10MHz.   
Measurements were made by changing the SPI clock frequency.   
The measurement result is [FPS].   
__Wire cables should be as short as possible.__   
|SoC@CPU Freq|1MHz|2MHz|4MHz|6MHz|8MHz|10MHz||
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
|ESP32@160|90.3|143.8|224.6|272.0|297.0|316.3||
|ESP32@240|97.4|166.0|271.3|339.2|378.9|417.2||
|ESP32S2@160|94.5|159.4|244.4|301.0|331.8|356.0||
|ESP32S2@240|101.7|174.1|290.1|367.1|413.9|458.9||
|ESP32S3@160|93.7|152.2|240.7|295.0|324.4|347.5||
|ESP32S3@240|100.1|172.9|286.0|360.9|411.2|449.1||
|ESP32C2@120|91.6|150.7|226.7|263.5|295.5|314.5|26MHz XTAL|
|ESP32C3@160|98.0|164.2|265.5|328.1|365.0|394.6||
|ESP32C6@160|98.2|164.9|268.0|331.9|369.6|399.8||
|ESP32H2@96|86.6|139.1|202.8|235.5|256.1|267.9||

ESP32C6 gave the fastest results when the CPU frequency was 160MHz (120MHz or 96MHz for some SoCs).   
ESP32C3 is the next fastest.   
The difference between ESP32C6 and ESP32C3 is very small.   
![spi_160MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/18c415f7-24e6-4580-9f19-4a35668ad259)

![spi_160MHz-1MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/7bd69c24-886f-4507-8c1e-b0b826bcd302)
![spi_160MHz-2MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/0633b1b3-adf1-4039-a629-0e55a8f5b82d)
![spi_160MHz-4MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/b6ad92ff-47ef-4b97-b937-128353ca617c)
![spi_160MHz-6MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/126e891c-e4b6-41ff-8f71-f0d554406ecd)
![spi_160MHz-8MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/4973cd93-92ce-443f-b531-8d06853a0e61)
![spi_160MHz-10MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/0d700fa6-1857-4bb7-a3d4-8078b38be8a4)

ESP32S2 gave the fastest results when the CPU frequency was 240MHz.   
![spi_240MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/f8687aa9-039a-464c-8a75-c51667a0fb0f)

![spi_240MHz-1MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/5bf5100a-2c92-4016-afc6-b1b3549c9509)
![spi_240MHz-2MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/03423564-b576-400e-821f-e80c0ae19fda)
![spi_240MHz-4MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/dc011894-c387-47de-b6d5-64ffa3d08582)
![spi_240MHz-6MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/95a45a4a-dc8d-4257-ac24-27211b990c46)
![spi_240MHz-8MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/129eb963-8d27-41c6-9c42-22330d1abdc2)
![spi_240MHz-10MHz](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/abfcd92a-90b6-4bb8-8c97-941b5fc4e331)

__Note:__   
Please note that this benchmark results from ESP-IDF V5.2.   
Your results may vary if you use other versions.   

