# RoraryEncoderDemo for SSD1306
We got an SSD1306 with rotary encoder like this.   
So I played around with it a little.   
I used [this](https://github.com/nopnop2002/esp-idf-RotaryEncoder) component.   

I borrowed the BIT MAP data from [here](https://iitestudent.blogspot.com/2013/01/displaying-bitmap-on-graphic-lcd.html).   
The original image resolution is 420x200.   

![Image](https://github.com/user-attachments/assets/6628c203-2c3f-4b04-8cd9-e768f9a91aae)
![Image](https://github.com/user-attachments/assets/9857a8f5-5d56-4a27-afed-14f9cd68b8f0)

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


# Displaying images with a width of 240 dots or more   
Crop the original image to this image.   
The image below has a resolution of 420x64.   
![fleischer1](https://github.com/user-attachments/assets/31ca12b8-c932-45e6-b021-d17f9865141b)

Convert this image to a 128x64 image by shifting it by 8 dots, and display the converted image continuously.   
![fleischer1-1](https://github.com/user-attachments/assets/3979a98b-f239-4ddf-9294-1a59a2d6d170)   
![fleischer1-2](https://github.com/user-attachments/assets/b86e8f9a-247d-4913-b008-df908bbb08cf)   
![fleischer1-3](https://github.com/user-attachments/assets/3bca8693-94a1-4d3d-b7dc-62d9b1986379)   

# Display images with a height of 64 dots or more   
Crop the original image to this image.   
The image below has a resolution of 128x184.   
![fleischer2](https://github.com/user-attachments/assets/e04b71c6-8a3b-4a03-bc99-199ad489b67e)

Convert this image to a 128x64 image by shifting it by 8 dots, and display the converted image continuously.   
![fleischer2-1](https://github.com/user-attachments/assets/a578ae7d-e0df-47df-a2b9-cbdd2dd65d12)   
![fleischer2-2](https://github.com/user-attachments/assets/b82fd09e-b5a7-480e-9224-7bd31e095e42)   
![fleischer2-3](https://github.com/user-attachments/assets/810ed461-edfe-419b-b601-4059a4fddcbb)   
