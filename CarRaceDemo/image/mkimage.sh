#!/bin/bash

convert istockphoto-1282378168-1024x1024.jpg -crop 256x512+740+40 vehicle1.jpg
convert vehicle1.jpg -resize 24x vehicle1.jpg
convert istockphoto-1282378168-1024x1024.jpg -crop 256x512+30+32 vehicle2.jpg
convert vehicle2.jpg -resize 24x vehicle2.jpg
convert istockphoto-1282378168-1024x1024.jpg -crop 256x512+138+512 vehicle3.jpg
convert vehicle3.jpg -resize 24x vehicle3.jpg

# Crop image
convert 365470.jpg -crop 382x382+106+125 _highway1.jpg

convert _highway1.jpg -resize 128x _highway1.jpg


convert _highway1.jpg -fill "#FFFFFF" -draw "rectangle  0, 0, 43, 127" _highway5.jpg

convert _highway5.jpg -fill "#FFFFFF" -draw "rectangle  85 0, 127, 127" _highway5.jpg


convert _highway5.jpg -fill "#FFFFFF" -draw "rectangle  79, 0, 127, 127" _highway6.jpg

convert _highway5.jpg -fill "#FFFFFF" -draw "rectangle  0, 0, 49, 127" _highway7.jpg
convert _highway7.jpg -roll -50+0 _highway71.jpg

convert _highway5.jpg -fill "#FFFFFF" -draw "rectangle  0, 0, 61, 127" _highway8.jpg

convert _highway8.jpg -fill "#FFFFFF" -draw "rectangle  79, 0, 127, 127" _highway9.jpg
convert _highway9.jpg -roll -62+0 _highway91.jpg



convert _highway6.jpg -roll -34+0 highway_width.jpg

convert highway_width.jpg _highway91.jpg -gravity northwest -geometry +45+0 -compose over -composite highway_width.jpg

convert highway_width.jpg _highway91.jpg -gravity northwest -geometry +62+0 -compose over -composite highway_width.jpg

convert highway_width.jpg _highway91.jpg -gravity northwest -geometry +79+0 -compose over -composite highway_width.jpg

convert highway_width.jpg _highway71.jpg -gravity northwest -geometry +83+0 -compose over -composite highway_width.jpg

# Split image in half
convert highway_width.jpg -crop 128x64+0+0 highway_width0.jpg

rm _highway*.jpg
