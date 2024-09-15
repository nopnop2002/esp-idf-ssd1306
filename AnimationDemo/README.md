# AnimationDemo for SSD1306

![AnimationDemo](https://user-images.githubusercontent.com/6020549/165405896-e37ff7f1-f118-4090-95e9-6f940989c6a4.JPG)

![esp32s2-pcb-2](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/546f0fe8-c565-4b58-8edf-6f9a644f0f5f)

I borrowed the BIT MAP data from [here](https://www.mischianti.org/2021/07/14/ssd1306-oled-display-draw-images-splash-and-animations-2/).   

__Wire cables should be as short as possible.__   
I used a 10 cm wire cable.   
However, it is sometimes affected by noise.   

__Flip upside down cannot be enabled.__   

__This demo does not support 128x32 panels.__   

The SPI interface operates faster than the I2C interface.   
For SPI interfaces, there has a latency period between frames.   
By making this smaller, you can display it even faster.   

