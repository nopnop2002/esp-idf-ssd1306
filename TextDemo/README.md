# TextDemo for SSD1306

![TextDemo](https://user-images.githubusercontent.com/6020549/165234668-eee65290-c5d3-4ca4-aa51-3c8225ead910.JPG)

This repository uses [this](https://github.com/dhepper/font8x8) font file by default.   
However, this repository is a 90 degree transposed font of the original font.   
High-speed drawing is achieved by 90 degree transposition.   
If you use the original font, you must transpose it 90 degrees.   

```
#include "font8x8_ext_latin.h"
#include "font8x8_greek.h"

    uint8_t image[8];
    memcpy(image, font8x8_ext_latin[2], 8);
    ssd1306_rotate_image(image, true);
    ssd1306_display_image(&dev, 0, 0, image, 8);
    memcpy(image, font8x8_greek[2], 8);
    ssd1306_rotate_image(image, true);
    ssd1306_display_image(&dev, 1, 0, image, 8);
```

![IMG_5978](https://github.com/user-attachments/assets/d87659b8-5f2f-4a07-adb7-c23f33e7fc83)

---

You can also use True Type Font and BDF Font.

Using BDF Font.   
https://github.com/nopnop2002/esp-idf-ssd1306/tree/master/BdfFontDemo   

Using True Type Font.   
https://github.com/nopnop2002/esp-idf-ssd1306/tree/master/FreeTypeDemo   
