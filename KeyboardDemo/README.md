# KeyboardDemo for SSD1306
Demo that displays input from the keyboard.   
I used [this](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/usb/host/hid) as a reference.   

![usb-keyboard-1](https://github.com/user-attachments/assets/cb108559-4a5a-4df7-9be8-47f9f4c492f3)

# Hardware requirements

- ESP32S2/S3   
 These have USB-HOST functionality.

- USB Connector   
 I used this:   
 ![usb-conector-2](https://github.com/user-attachments/assets/7551058f-2647-4618-b143-3e4a77df5fc2)

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
