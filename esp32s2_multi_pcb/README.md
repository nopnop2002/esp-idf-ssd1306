# ESP32S2 Mini Multi PCB
Several products of ESP32 equipped with SSD1306 are available.   
However, I have never seen a product equipped with an SSD1306 with an SPI interface.   
Also, I have never seen a product equipped with a 1.3 inch SSD1306 product.   
Therefore, I designed a PCB that can be equipped with an SPI interface and 1.3 inch products.   
I use ESP32S2-Mini Development board.   
Although this product is very small, it is equipped with 2MB of PSRAM.   

![esp32s2-pcb-1](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/c7c7a839-b397-4d8b-b8b5-fc1f75a73ad3)
![esp32s2-pcb-2](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/546f0fe8-c565-4b58-8edf-6f9a644f0f5f)
![esp32s2-pcb-3](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/75cec085-c336-453c-b10e-0d3ba5e59ede)
![esp32s2-pcb-4](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/8ebc94ee-1ff9-4591-a0a5-3057ea397bf2)


# Configuration   
for SPI interface   
![config-spi](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/3a3e85de-dfc9-4888-bf2f-3e211e0a7bac)

for I2C interface   
![config-i2c](https://github.com/nopnop2002/esp-idf-ssd1306/assets/6020549/ab8a9f3b-e4d7-41e7-a658-3173f847f711)

# Why ESP32S2 Mini?
Cheap!!   
Only $1.49 excluding shipping.   
I bought two and it cost $4.27 including shipping.   

# About ESP32S2 Mini
A Type-C USB connector is mounted on the board, but a USB-TTL conversion chip is not mounted.   
The circuit diagram is available [here](https://www.wemos.cc/en/latest/_static/files/sch_s2_mini_v1.0.0.pdf).   
USB ports D- and D+ are connected to GPIO19/20.   
Since it uses the chip's USB-OTG function, it will not be recognized as a USB device even if you simply connect it to the host with a USB cable.   
To write firmware, press ButtonRST while pressing Button0, then release ButtonRST and then Button0.   
Now the device will enter DFU mode, the USB device (/dev/ttyACM0) will appear, and you can upload the firmware.   
Once the firmware upload is complete, press ButtonRST again.   
The firmware will now start.   
If you press ButtonRST without pressing Button0, the USB device will disappear.   

To use STDOUT, you need to change Channel for console output to USB CDC in menuconfig.   
![esp32-s2-mini-4](https://github.com/user-attachments/assets/d9dab093-7882-4f57-a978-38fa69c71bb6)

After changing Channel for console output to USB CDC in menuconfig, upload the firmware again.   
Once the firmware has been uploaded, the following display will appear.   
![esp32-s2-mini-5](https://github.com/user-attachments/assets/32f7e2e9-b50c-423f-ac93-9081995c7763)

__Now press ButtonRST.__   
The firmware with USB CDC enabled will now start running.   
From now on, you will be able to write and monitor the firmware without pressing Button0 or ButtonRST.

This board has 4MB of FLASH and ___2MB of PSRAM___.   
It's strange that it is recognized as having an external flash.   
There is no external flash anywhere on the board.   
![esp32-s2-mini-6](https://github.com/user-attachments/assets/f185ad9b-299b-4c23-a63a-63ed4404af3f)

# Enable PSRAM   
ESP32S2's RAM is very small.   
You can avoid running out of memory by enabling PSRAM.   
In order to use PSRAM, you need to enable PSRAM by following the steps below.   
Please note that this procedure is for ESP-IDF V5.2 and may change in the future.   
![psram-1](https://github.com/nopnop2002/esp-idf-net-logging/assets/6020549/9feae820-609d-4955-94d0-2d7e4e5887ab)
![psram-2](https://github.com/nopnop2002/esp-idf-net-logging/assets/6020549/3b6c8c0a-380f-492e-b72a-74d408c73fb0)
![psram-3](https://github.com/nopnop2002/esp-idf-net-logging/assets/6020549/a72b8638-8de1-4c9e-b8e1-98562e2b515e)
![psram-4](https://github.com/nopnop2002/esp-idf-net-logging/assets/6020549/ae980ac1-470e-4b9d-bd2b-82ec4777f204)
![psram-5](https://github.com/nopnop2002/esp-idf-net-logging/assets/6020549/76a7a4f3-e231-4509-b997-c1d710ee7301)

# How to order PCB   
You can repeat my order from [here](https://www.pcbway.com/project/shareproject/esp32s2_ssd1306_multi_pcb_2d6e5b26.html).   

# Why PCBWay?
I have used several PCB manufacturers in the past, but lately I have only used PCBWay.   

- Quality and Reliability   
 PCBWay's PCBs meet the highest standards of quality and reliability, they are also capable of meeting the technical demands of any project, from simple projects like mine to very complicated projects.

- Customization and Flexibility   
 They offer extensive customization options, allowing board designers to tailor their PCBs precisely to their project's needs.

- Easy order   
 Many PCB manufacturers have pages for ordering, but PCBWay's ordering page is the easiest to use.   
 This is very important to me as English is not my native language.   
 The easiest way to order is to select your PCB size, Quantity and Solder Mask color. Other selections remain default.   
 PCBWay will provide you with a price after verifying the validity of your board manufacturing information.   

- Shipping options   
 I always use the cheaper option and am very happy with the delivery quality and delivery time.   
 It will arrive in Japan in about 7 to 10 days.   
 You can further reduce delivery time by choosing another option.   

