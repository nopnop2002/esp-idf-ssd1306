#!/bin/bash

# Download the cloud image from here. Resize the image to width 128.
# https://www.vecteezy.com/vector-art/28199306-clouds-icon-vector-illustration

convert cloud1.jpg -crop 68x34+0+14 cloud11.jpg
convert cloud11.jpg -resize 64x cloud11.jpg

convert cloud1.jpg -crop 80x40+48+10 cloud12.jpg
convert cloud12.jpg -resize 64x cloud12.jpg
convert cloud12.jpg -roll -5+0 cloud12.jpg

convert cloud1.jpg -crop 68x34+0+14 cloud13.jpg
convert cloud13.jpg -resize 64x cloud13.jpg

convert cloud1.jpg -crop 80x40+48+64 cloud14.jpg
convert cloud14.jpg -resize 64x cloud14.jpg
convert cloud14.jpg -roll -5+0 cloud14.jpg

