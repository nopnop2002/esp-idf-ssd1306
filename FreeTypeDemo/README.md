# FreeTypeDemo for SSD1306

FreeType components are published in the ESP Component Registry.   
The github page is [here](https://github.com/espressif/idf-extra-components/tree/master/freetype).   
This component can convert a True Type Font to a bitmap image.   

___Please note that if you use a proportional font, some fonts may not convert correctly.___   
Monospaced fonts can be converted correctly.   
You can find Monospaced fonts [here](https://en.wikipedia.org/wiki/List_of_monospaced_typefaces).   

![FreeTypeDemo](https://github.com/user-attachments/assets/13892a84-8ed8-48b9-8e1e-8e1f7235f8cb)

# How to use true type font.

- Download Monospaced fonts from internet.

- Copy font file to fonts directory.

- Select font   
  load_font("/fonts/consola.ttf");

- Specify the display position and threshold   
  render_text(&dev, 0, 16, 128, "FreeType");

