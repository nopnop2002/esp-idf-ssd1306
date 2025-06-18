#!/bin/bash
identify fleischer_420.jpg
# fleischer_420.jpg JPEG 420x200 420x200+0+0 8-bit sRGB 16274B 0.000u 0:00.000

# Crop to 420x64 image
convert fleischer_420.jpg -crop 420x64+0+10 fleischer1.jpg
convert fleischer_1.jpg -crop 128x64+100+10 fleischer1-1.jpg
convert fleischer_1.jpg -crop 128x64+108+10 fleischer1-2.jpg
convert fleischer_1.jpg -crop 128x64+116+10 fleischer1-3.jpg

identify fleischer1.jpg
# fleischer1.jpg JPEG 420x64 420x64+0+0 8-bit Gray 256c 6488B 0.000u 0:00.000

# Crop to 128x184 image
convert fleischer_420.jpg -crop 128x184+144+10 fleischer2.jpg
convert fleischer2.jpg -crop 128x64+0+0 fleischer2-1.jpg
convert fleischer2.jpg -crop 128x64+0+8 fleischer2-2.jpg
convert fleischer2.jpg -crop 128x64+0+16 fleischer2-3.jpg

identify fleischer2.jpg
# fleischer2.jpg JPEG 128x184 128x184+0+0 8-bit Gray 256c 8027B 0.000u 0:00.000
