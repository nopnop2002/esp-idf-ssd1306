# ImageScrollDemo for SSD1306

![ImageScrollDemo](https://user-images.githubusercontent.com/6020549/183776833-692411ca-9464-4fe7-afea-cddcbd5901ae.JPG)

I borrowed the BIT MAP data from [here](https://www.iconspng.com/search.php?png=16+segment+display).   



# How to make Alphabet image   
- Download png file.   
- Eliminate shadows using Windows paint.   
- Convert image to monochrome using convert.   
```
convert [in] -monochrome [out]
```
- Eliminate dot-line using Windows paint.   
- Resize image to 48x62 using convert.   
```
convert [in] -resize -x48 [out]
```
- Convert image file to BMP data using this [page](https://www.mischianti.org/2021/07/14/ssd1306-oled-display-draw-images-splash-and-animations-2/).   
- Paste the BMP data into your code.


