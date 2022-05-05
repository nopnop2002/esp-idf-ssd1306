# MeterDemo for SSD1306

![MeterDemo](https://user-images.githubusercontent.com/6020549/166136718-5139deb8-df11-4756-b161-7830ce2251ea.JPG)

I borrowed the BIT MAP data from [here](https://forum.arduino.cc/t/analog-vu-meter-i2c-oled-sh1106-oledmeter-animation/388374).   

__Wire cables should be as short as possible.__   

I used a 10 cm wire cable.   
However, it is sometimes affected by noise.   

# Convert from BITMAP data to Page and Segment   
This sample shows how to quickly redraw a BITMAP image.   
High-speed drawing is possible by converting BITMAP data to Page and Segment.   
You can use ssd1306_bitmaps function as converter.   


# Analog source   
You will need an analog source to run this demo.   
Connect the analog source to the following GPIO.   
These are all channel 0 of ADC1.   

- Analog input gpio for ESP32 is GPIO36. 12Bits width.   
- Analog input gpio for ESP32S2 is GPIO01. 13Bits width.   
- Analog input gpio for ESP32S3 is GPIO01. 12Bits width.   
- Analog input gpio for ESP32C3 is GPIO00. 12Bits width.   

Schematic I used:
```
ESP32 3V3 ----------- CDS ---+---+
                             |   |
ESP32 Analog input ----------+   |
                                 |
ESP32 GND ------ Register -------+
```

