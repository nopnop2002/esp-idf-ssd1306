# HighwayDemo for SSD1306

![Highway-1](https://github.com/user-attachments/assets/110aa599-4794-430b-bf05-4ab843510f4c)
![Highway-2](https://github.com/user-attachments/assets/8b7ba9ef-e1b4-4cb8-8e4c-abf8a6fad234)

I found this public image on the internet.   
So I played around with it a bit.   
This is a demo that's just for fun and doesn't help anyone.   

![_451034](https://github.com/user-attachments/assets/97ed02c4-6432-4b6a-8808-49a7fe850abf)
![_365470](https://github.com/user-attachments/assets/897ab40a-f152-4b24-bc0f-43f8b7002291)
![_451033](https://github.com/user-attachments/assets/97fa5f1f-a1f2-421d-afca-8f83f532a39d)

__Wire cables should be as short as possible.__   
I used a 10 cm wire cable.   
However, it is sometimes affected by noise.   

__This demo does not support 128x32 panels.__   

The SPI interface operates faster than the I2C interface.   
For SPI interfaces, there has a latency period between frames.   
By making this smaller, you can display it even faster.   

