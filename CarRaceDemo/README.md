# CarRaceDemo for SSD1306

![CarRaceDemo](https://github.com/user-attachments/assets/ba48d335-7ea5-45d8-983d-322c145d856b)

I found this public image on the internet.   
So I played around with it a bit.   
This is a demo that's just for fun and doesn't help anyone.   

![_365470](https://github.com/user-attachments/assets/897ab40a-f152-4b24-bc0f-43f8b7002291)

__Wire cables should be as short as possible.__   
I used a 10 cm wire cable.   
However, it is sometimes affected by noise.   

__This demo does not support 128x32 panels.__   

The SPI interface operates faster than the I2C interface.   
For SPI interfaces, there has a latency period between frames.   
By making this smaller, you can display it even faster.   

