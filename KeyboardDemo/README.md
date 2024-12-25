# KeyboardDemo for SSD1306
Demo that displays input from the keyboard.   
I used [this](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/usb/host/hid) as a reference.   

![usb-keyboard-1](https://github.com/user-attachments/assets/cb108559-4a5a-4df7-9be8-47f9f4c492f3)

# Hardware requirements

- ESP32S2/S3   
 These have USB-HOST functionality.

- USB Connector   
 I used this:   
 ![usb-conector-3](https://github.com/user-attachments/assets/05f3f79d-00d1-4d65-ad46-67d2e987bc88)   
 We can buy this breakout on Ebay or AliExpress.   
 ![usb-conector-11](https://github.com/user-attachments/assets/848998d4-fb0c-4b4f-97ae-0b3ae8b8996a)   
 ![usb-conector-12](https://github.com/user-attachments/assets/6fc34dcf-0b13-4233-8c71-07234e8c6d06)   

- USB keyboard   

# USB wiring   
To stabilize the power supply, I placed a 100uF electrolytic capacitor between 5V and GND.   
```
ESP32-S2/S3 BOARD           USB CONNECTOR
                            +--+
    [  5V   ]  +--------->  | || VCC
    [GPIO 19]  |--------->  | || D-
    [GPIO 20]  |--------->  | || D+
    [  GND  ]  |--------+>  | || GND
               |        |   +--+
               +---||---+
                  100uF
```

# USB hot socket
There are times when it works correctly and times when it doesn't.   
It works more stably if you connect before starting the firmware.   
When it works correctly, a log like this will be displayed.   
```
I (796) usb_hid: hid_host_device_callback
I (796) usb_hid: HID Device, protocol 'KEYBOARD' CONNECTED
I (806) usb_hid: hid_host_device_callback
I (816) usb_hid: HID Device, protocol 'NONE' CONNECTED
```

# Using USB-HUB
I tried it, but it doesn't work properly via USB-HUB.

# Transfer failed error
For some reason, the following error may occur in rare cases.   
This error occurs within [this](https://components.espressif.com/components/espressif/usb_host_hid) component.   
It is unclear whether it is a component bug or an effect of electrical noise.   
Some kind of stabilization circuitry may be required.   
It may come back to life if you unplugging the keyboard and plugging it again.   
I would like to hear the opinion of someone who is familiar with USB electrical circuits.   
```
E (12287696) hid-host: Transfer failed, status 1
E (12287696) usb_hid: HID Device, protocol 'KEYBOARD' TRANSFER_ERROR
E (15953516) USBH: Device 1 gone
```
