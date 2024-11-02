# MultiDeviceDemo for SSD1306

## For I2C
The I2C address of SSD1306 is 0x3c.   
Some modules can change the I2C address to 0x3d by changing the chip resistor on the back.   
![MultiDeviceDemo-I2C-1](https://github.com/user-attachments/assets/663044f7-d7bb-4558-8a7a-1145ef5a4393)   

You can check the I2C address using [this](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/i2c/i2c_tools).   
![MultiDeviceDemo-I2C-2](https://github.com/user-attachments/assets/e6678d0c-4b65-4b8f-bb7d-d0e91a3f9523)

By changing the I2C address, up to two SSD1306 can be used at the same time.
![MultiDeviceDemo-I2C-3](https://github.com/user-attachments/assets/4ba02799-9110-4215-b3fc-b1722b11df61)   

### Wireing    
|ESP32||SSD1301#1|SSD1302#2|
|:-:|:-:|:-:|:-:|
|GPIO21(*1)|--|SDA|SDA|
|GPIO22(*1)|--|SCL|SCL|
|Vcc|--|VCC|VCC||
|GND|--|GND|GND||

(*1) You can change using menuconfig.   

## For SPI
The ESP-IDF's SPI master has 6 CS lines to drive up to 6 SPI slaves.   
By changing the CS line, up to six SSD1306 can be used at the same time.   
![MultiDeviceDemo-SPI](https://github.com/user-attachments/assets/3d8cbe1e-a882-468e-8299-c2ddd070bc12)

### Wireing    
|ESP32||SSD1301#1|SSD1302#2|
|:-:|:-:|:-:|:-:|
|GPIO16(*2)|--|CS||
|GPIO17(*2)|--||CS|
|GPIO04(*1)|--|DC|DC|
|GPIO15(*1)|--|RES|RES|
|GPIO23(*1)|--|MOSI|MOSI|
|GPIO18(*1)|--|SCLK|SCLK|
|Vcc|--|VCC|VCC||
|GND|--|GND|GND||

(*1) You can change using menuconfig.   

(*2) You can change this by editing main.c.   
