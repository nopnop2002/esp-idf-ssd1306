# FreeTypeDemo for SSD1306

FreeType components are available from the ESP Component Registry.   
https://components.espressif.com/components/espressif/freetype/   

The github page is [here](https://github.com/espressif/idf-extra-components/tree/master/freetype).   
This component can convert a True Type Font to a bitmap image.   

___Please note that if you use a proportional font, some fonts may not convert correctly.___   
Monospaced fonts can be converted correctly.   
You can find Monospaced fonts [here](https://en.wikipedia.org/wiki/List_of_monospaced_typefaces).   
You can find more Monospaced fonts if you search.   

![FreeTypeDemo](https://github.com/user-attachments/assets/13892a84-8ed8-48b9-8e1e-8e1f7235f8cb)

# How to use True Type font.

- Download Monospaced fonts from internet.

- Copy font file to fonts directory.

- Select font.   
  ```load_font("/fonts/consola.ttf");```

- Specify the display position and threshold.   
  The converted bitmap is monochrome data with gradations from 0 to 255.   
  The lower the value, the lighter the black, and the higher the value, the darker the black.   
  Unfortunately, SSD1306 cannot express gradations.   
  The lower the threshold, the small value will display. As a result, the text becomes thicker.   
  The higher the threshold, the small value will not display. As a result, the text becomes thinner.   
  ```render_text(&dev, 0, 16, 128, "FreeType");```


# Bitmap gradation representation
```
________
________
________
___####_
__##.+##
_+#___.#
_##____#
_#######
_##.....
_+#_____
__##+.+#
___####+
________
________
________
________
```

\# indicates a value greater than 128.   
\+ indicates that the value is greater than 64 and less than 128.   
. indicates that the value is greater than 32 and less than 64.   
_ indicates a value less than 32.

Setting the threshold to 128 will only show # pixels.   
The first and second fonts in the photo use the same font file (consola.ttf), but are displayed with different thresholds.   
```
________
________
________
___####_
__##__##
_ #____#
_##____#
_#######
_##_____
_ #_____
__##___#
___####_
________
________
________
________
```
