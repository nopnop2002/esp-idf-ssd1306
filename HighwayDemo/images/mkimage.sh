#!/bin/bash

convert 365470.jpg -resize 128x _365470.jpg

# Crop image
convert 365470.jpg -crop 382x382+106+125 highway1.jpg

convert highway1.jpg -resize 128x _highway1.jpg

# Split image in half
convert _highway1.jpg -crop 128x64+0+0 highway11.jpg
convert _highway1.jpg -crop 128x64+0+64 highway12.jpg


convert 451034.jpg -resize 128x _451034.jpg

# Crop image
convert 451034.jpg -crop 382x382+106+125 highway2.jpg

convert highway2.jpg -resize 128x _highway2.jpg

# Split image in half
convert _highway2.jpg -crop 128x64+0+0 highway21.jpg
convert _highway2.jpg -crop 128x64+0+64 highway22.jpg


convert 451033.jpg -resize 128x _451033.jpg

# Crop image
convert 451033.jpg -crop 240x240+180+200 _highway31.jpg

convert _highway31.jpg -resize 128x _highway32.jpg

# Move image horizontally
convert _highway32.jpg -distort Affine '31,0 0,0' _highway3.jpg

# Split image in half
convert _highway3.jpg -crop 128x64+0+0 highway31.jpg
convert _highway3.jpg -crop 128x64+0+64 highway32.jpg

# Flip image horizontally
convert -flop _highway31.jpg  _highway41.jpg

convert _highway41.jpg -resize 128x _highway42.jpg

# Move image horizontally
convert _highway42.jpg -distort Affine '33,0 0,0' _highway4.jpg

# Split image in half
convert _highway4.jpg -crop 128x64+0+0 highway41.jpg
convert _highway4.jpg -crop 128x64+0+64 highway42.jpg

