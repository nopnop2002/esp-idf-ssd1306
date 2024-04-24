# BlinkIconDemo for SSD1306

![BlinkIconDemo-1](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/ce0becb9-43d2-43a6-8c53-eceda48f0524)
![BlinkIconDemo-2](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/fc3b5d11-4c58-471d-b73e-e59616abc3b6)


I borrowed the BIT MAP data from here.   
https://thenounproject.com/icon/receive-data-3177814/   
https://thenounproject.com/icon/receive-data-3177850/   
https://thenounproject.com/icon/data-send-3753756/   
https://thenounproject.com/icon/data-send-3753855/   


# How to make your original BIT MAP data   
- Prepare your image file.   
- Convert image file to JPEG format.
- Resize image file to 128x64.
 I used this.
 ```convert input.jpg -resize x64 output.jpg```
- Convert image file to BMP data using [this](https://www.mischianti.org/2021/07/14/ssd1306-oled-display-draw-images-splash-and-animations-2/) page.   
- Paste the BMP data into your code.   


