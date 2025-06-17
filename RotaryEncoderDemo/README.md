# RoraryEncoderDemo for SSD1306
We got an SSD1306 with rotary encoder like this.   
So I played around with it a little.   
I used [this](https://steemit.com/utopian-io/@pakganern/oled-display-gauge-meter-using-potentiometer-arduino) article as a reference.   
I used [this](https://github.com/nopnop2002/esp-idf-RotaryEncoder) component.   

![Image](https://github.com/user-attachments/assets/123c9a0d-a319-40c7-9466-3cbf274034c5)
![Image](https://github.com/user-attachments/assets/3eae2f51-2075-484a-8a35-e37f98777f4a)

# Configuration
![Image](https://github.com/user-attachments/assets/d50b2d41-3280-40f3-8ca2-4f48a8a2eb15)
![Image](https://github.com/user-attachments/assets/9011ef19-c63f-41f0-861c-e234531f7bc5)

# Wirering
|Device||ESP32|ESP32-S2/S3|ESP32-C2/C3/C6||
|:-:|:-:|:-:|:-:|:-:|:-:|
|VCC|--|3V3|3V3|3V3||
|GND|--|GND|GND|GND||
|BAK|--|N/C|N/C|N/C|(*2)|
|TRB|--|GPIO16|GPIO16|GPIO02|(*1)|
|TRA|--|GPIO15|GPIO15|GPIO01|(*1)|
|PSH|--|GPIO17|GPIO17|GPIO03|(*1)|
|SCL|--|GPIO22|GPIO02|GPIO06|(*1)|
|SDA|--|GPIO21|GPIO01|GPIO05|(*1)|
|CON|--|N/C|N/C|N/C|(*2)|

(*1) You can change any GPIO using menuconfig.   

(*2) These ports are simple digital ports. Not used in this project.   

This demo also works with generic SPI panels and KY-040 RotaryEncoder.   
![Image](https://github.com/user-attachments/assets/2dd99695-11a2-44fd-83f0-a3f023d2a8cc)
