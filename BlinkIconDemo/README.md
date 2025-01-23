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


# Hwo to use Bootstrap Icons   
There are over 2000 icons available [here](https://icons.getbootstrap.com/).    
All icons are free to use.   
On [this](https://www.mischianti.org/2021/07/14/ssd1306-oled-display-draw-images-splash-and-animations-2/) site, you can create BMP data from not only JPEG and PNG files, but also SVG files.   
If you need to change (enlarge) the icon size, you can enlarge it on [this](https://svgtrace.com/svg-to-png) site.   
__The icon width must be a multiple of 8 pixels.__   
Now you don't have to worry about icons anymore.   
![Image](https://github.com/user-attachments/assets/82b3b11f-8388-4a82-b648-e3686ff7a270)
