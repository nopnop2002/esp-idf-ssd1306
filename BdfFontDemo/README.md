# BdfFontDemo for SSD1306

![BdfFontDemo-1](https://github.com/user-attachments/assets/df733de1-b5b8-4142-8123-5a8f992246ff)
![BdfFontDemo-2](https://github.com/user-attachments/assets/224d12c4-8ecf-4116-868a-8f11ca480122)
![BdfFontDemo-3](https://github.com/user-attachments/assets/4dbb6f39-ae0f-4ca2-9e55-ba32476b018e)

u8g2 is a great Library for monochrome displays.   
This library contains a lot of BDF format fonts.   
This project is a demo that displays BDF format fonts.   

# How to use BDF Font
- Download the BDF font file.   
 Thank you olikraus for releasing useful software.   

```
cd $HOME
git clone https://github.com/olikraus/u8g2
ls $HOME/u8g2/tools/font/bdf
```

- Convert BDF font files to header files.   
 I based it on [this](https://github.com/pixelmatix/bdf2c).   
 Thank you Pixelmatix for releasing useful software.   
```
cd esp-idf-ssd1306/BdfFontDemo
cc -o bdf2c bdf2c.c
```

Specify the font variable name with the -n option.   
```
./bdf2c -n ncenR12 -b < $HOME/u8g2/tools/font/bdf/ncenR12.bdf > main/ncenR12.h

./bdf2c -n timR12 -b < $HOME/u8g2/tools/font/bdf/timR12.bdf > main/timR12.h

./bdf2c -n emoticons -b < $HOME/u8g2/tools/font/emoticons/emoticons21.bdf > main/emoticons.h

./bdf2c -n Scroll_o_Sprites -b < $HOME/u8g2/tools/font/pbm/Scroll-o-Sprites.bdf > main/Scroll-o-Sprites.h
```

Characters that cannot be used in C language variable names will result in an error during compilation.   
This is unacceptable.   
```
./bdf2c -n Scroll-o_Sprites -b < $HOME/u8g2/tools/font/pbm/Scroll-o-Sprites.bdf > main/Scroll-o-Sprites.h
```


- BDF font files can be viewed with the following command.
```
./bdf2c -B < $HOME/u8g2/tools/font/bdf/ncenR12.bdf | more

./bdf2c -B < $HOME/u8g2/tools/font/bdf/timR12.bdf | more

./bdf2c -B < $HOME/u8g2/tools/font/emoticons/emoticons21.bdf | more

./bdf2c -B < $HOME/u8g2/tools/font/pbm/Scroll-o-Sprites.bdf | more
```

- Add header files to main.c.
```
#include "ncenR12.h"
#include "timR12.h"
#include "emoticons.h"
#include "Scroll-o-Sprites.h"
```


- Show BDF Font
```
ssd1306_clear_screen(&dev, false);
ssd1306_contrast(&dev, 0xff);
show_bdf_font_text(&dev, __ncenR12_bitmap__, "Hello World", 0, 0);
```


# Font display position
The font's display position starts from the upper left corner of this image.   
Therefore, there will be some white space above the font.   
```
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
______XX,X_______,________,
_____X__,_X______,________,
____X___,_XX_____,________,
____XX__,_XX_____,________,
____XX__,_XX_____,________,
________,XX______,________,
________,X_______,________,
_______X,________,________,
______X_,__X_____,________,
_____X__,__X_____,________,
____XXXX,XXX_____,________,
____XXXX,XXX_____,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
```

# Font bounding box and character bounding box
BDF font file has a font bounding box (FONTBOUNDINGBOX).   
This FONTBOUNDINGBOX value indicates that all fonts must have a 3-pixel margin to the left and a 6-pixel margin below the font.   
By providing a FONTBOUNDINGBOX, this can omit the left edge and top and bottom whitespace from the font pattern.   

```
FONTBOUNDINGBOX 21 26 -3 -6
```

Each character has a character-specific bounding box (BBX).   
This BBX value indicates that this character is 8 dots wide by 12 dots high, and requires a 1 pixel margin to the left of this character.   
By providing a character-specific bounding box (BBX), this can omit the left edge whitespace from the font pattern.   
```
STARTCHAR d
ENCODING 100
SWIDTH 574 0
DWIDTH 10 0
BBX 8 12 1 0
BITMAP
0E
06
06
06
3E
66
C6
C6
C6
C6
66
3B
ENDCHAR
```

Fonts that take character-specific bounding boxes (BBX) into account can be modified as follows.   
This creates a 1 pixel whitespace on the left edge.   
DWIDTH will also change according to this change.   
```
STARTCHAR d
ENCODING 100
SWIDTH 574 0
DWIDTH 11 0
BBX 9 12 0 0
BITMAP
07
03
03
03
1F
33
63
63
63
63
33
1D8
ENDCHAR
```

Fonts that take character-specific bounding box (BBX) and font bounding box (FONTBOUNDINGBOX) into consideration change as follows.   
DWIDTH will also change according to this change.   
```
STARTCHAR d
ENCODING 100
SWIDTH 574 0
DWIDTH 14 0
BBX 14 26 0 0
BITMAP
00
00
00
00
00
00
00
00
00E0
0060
0060
0060
03E0
0660
0C60
0C60
0C60
0C60
0660
030B
00
00
00
00
00
00
ENDCHAR
```

Both the font bounding box (FONTBOUNDINGBOX) and character-specific bounding box (BBX) determine pixels position.   
This creates a 4 pixel whitespace on the left edge.   
This creates a 6 pixel whitespace on the buttomt edge.   
This image takes into account the font bounding box (FONTBOUNDINGBOX) and character-specific bounding box (BBX).   
```
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,XXX_____,________,
________,_XX_____,________,
________,_XX_____,________,
________,_XX_____,________,
______XX,XXX_____,________,
_____XX_,_XX_____,________,
____XX__,_XX_____,________,
____XX__,_XX_____,________,
____XX__,_XX_____,________,
____XX__,_XX_____,________,
_____XX_,_XX_____,________,
______XX,X_XX____,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
________,________,________,
```

Font width pixel is 14 dots, so this is what is actually displayed.   
```
________,______,
________,______,
________,______,
________,______,
________,______,
________,______,
________,______,
________,______,
________,XXX___,
________,_XX___,
________,_XX___,
________,_XX___,
______XX,XXX___,
_____XX_,_XX___,
____XX__,_XX___,
____XX__,_XX___,
____XX__,_XX___,
____XX__,_XX___,
_____XX_,_XX___,
______XX,X_XX__,
________,______,
________,______,
________,______,
________,______,
________,______,
________,______,
```

Changing FONTBOUNDINGBOX changes the character spacing.   
```FONTBOUNDINGBOX 21 26 -3 -6```   
A space of at least 3 pixels is generated between characters.   
![BdfFontDemo-1](https://github.com/user-attachments/assets/df733de1-b5b8-4142-8123-5a8f992246ff)

```FONTBOUNDINGBOX 21 26 -1 -6```   
A space of at least 1 pixels is generated between characters.   
![BdfFontDemo-4](https://github.com/user-attachments/assets/45dd3fab-a5df-4bc1-8436-6c7883001d93)


# Header file format   
This indicates the width of the FONTBOUNDINGBOX.   
```
// fontboundingbox_width
21,
```

This indicates the height of the FONTBOUNDINGBOX.   
```
// fontboundingbox_height
26,
```

This shows the font information for the characters.   
```
// 'd'
100,14,8,12,1,0,39,8,20,0x00,0xe0,0x00,0x00,---------------,0x00,0x00,0x00,
 |  |  | |  | | |  | |  |
 |  |  | |  | | |  | |  +- Font pattern
 |  |  | |  | | |  | +---- Last row in Y direction
 |  |  | |  | | |  +------ First row in Y direction
 |  |  | |  | | +--------- Number of font patterns
 |  |  | |  | +----------- BBX Y offset 
 |  |  | |  +------------- BBX X offset 
 |  |  | +---------------- BBX Y pixel
 |  |  +------------------ BBX X pixel
 |  +--------------------- Font width pixel
 +------------------------ Encoding
```

You can find out the width (in bytes) of this font using the following calculation:
```
{Number of font patterns} / ({Last row in Y direction} - {First row in Y direction} + 1)
```

In ths case:
```
39 / (20 - 8 + 1) = 3[bytes]
```

The font for lines 8 to 20 will be as follows:   
This is a bitmap of 24*13 pixels.   
```
0x00,0xe0,0x00,
0x00,0x60,0x00,
0x00,0x60,0x00,
0x00,0x60,0x00,
0x03,0xe0,0x00,
0x06,0x60,0x00,
0x0c,0x60,0x00,
0x0c,0x60,0x00,
0x0c,0x60,0x00,
0x0c,0x60,0x00,
0x06,0x60,0x00,
0x03,0xb0,0x00,
0x00,0x00,0x00,
```

You can display this bitmap with the following function.   
```
ssd1306_bitmaps(&dev, xpos, ypos+bdf_font.y_start, bitmap, 24, 13, false);
```

This marks the end of the font.   

```
// EOF
0,0,0,0,0,0,0,0,0
```


# BDF Font file editor
I use [this](http://hukka.ncn.fi/?fony).   
It's work fine on Windows10.   
There are probably many more.   

- Open BDF font file.   
 File->Import->BDF Font.   

![fony](https://github.com/user-attachments/assets/18c71509-9a66-4b23-a2cf-6ecc66bf5920)

- Save BDF font file.   
 File->Export->BDF Font.   


