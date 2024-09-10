# BdfFontDemo for SSD1306

![BdfFontDemo-1](https://github.com/user-attachments/assets/6e4fb518-c835-44ff-b457-ae6c53158f27)
![BdfFontDemo-2](https://github.com/user-attachments/assets/224d12c4-8ecf-4116-868a-8f11ca480122)
![BdfFontDemo-3](https://github.com/user-attachments/assets/4dbb6f39-ae0f-4ca2-9e55-ba32476b018e)

u8g2 is a great Library for monochrome displays.   
This library contains a large number of BDF format fonts.   
This project is a demo that displays BDF format fonts.   

# How to use BDF Font
- Download the BDF font file.
 ```
 git clone https://github.com/olikraus/u8g2
 ls $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/bdf
 ```

- Convert BDF font files to header files.   
 I used [this](https://github.com/pixelmatix/bdf2c) repository.   
 ```
 cc -o bdf2c bdf2c.c
 
 ./bdf2c -n ncenR12 -b < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/bdf/ncenR12.bdf > main/ncenR12.h
 
 ./bdf2c -n timR12 -b < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/bdf/timR12.bdf > main/timR12.h
 
 ./bdf2c -n battery -b < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/battery/battery19.bdf > main/battery.h
 
 ./bdf2c -n emoticons -b < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/emoticons/emoticons21.bdf > main/emoticons.h
 
 ./bdf2c -n Scroll_o_Sprites -b < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/pbm/Scroll-o-Sprites.bdf > main/Scroll-o-Sprites.h
 ```

- BDF font files can be viewed with the following command.
 ```
 ./bdf2c -B < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/bdf/ncenR12.bdf | more
 
 ./bdf2c -B < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/bdf/timR12.bdf | more
 
 ./bdf2c -B < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/battery/battery19.bdf | more
 
 ./bdf2c -B < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/emoticons/emoticons21.bdf | more
 
 ./bdf2c -B < $HOME/u8g2-hal-esp-idf/examples/i2c/components/u8g2/tools/font/pbm/Scroll-o-Sprites.bdf | more

- Add header files.
 ```
 #include "ssd1306.h"
 #include "ncenR12.h"
 #include "timR12.h"
 #include "battery.h"
 #include "emoticons.h"
 #include "Scroll-o-Sprites.h"
 ```


- Show BDF Font
 ```
 ssd1306_clear_screen(&dev, false);
 ssd1306_contrast(&dev, 0xff);
 show_bdf_font_text(&dev, __ncenR12_bitmap__, "Hello World", 0, 0); // You can change font file
 show_bdf_font_code(&dev, __battery_bitmap__, 48, 100, 0);
 show_bdf_font_code(&dev, __battery_bitmap__, 49, 110, 0);
 show_bdf_font_code(&dev, __battery_bitmap__, 50, 120, 0);
 ```