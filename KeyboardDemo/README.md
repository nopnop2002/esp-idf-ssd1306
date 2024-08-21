# KeyboardDemo for SSD1306
Demo that displays input from the keyboard.   
I used [this](https://components.espressif.com/components/espressif/usb_host_hid/) component.   

![usb-keyboard-1](https://github.com/user-attachments/assets/cb108559-4a5a-4df7-9be8-47f9f4c492f3)

# Hardware requirements

- ESP32S2/S3   
 These have USB-HOST functionality.

- USB Connector   
 I used this:   
 ![usb-conector](https://github.com/user-attachments/assets/a8fb5313-54f6-422a-98de-5f4aff8c94b7)

- USB keyboard   

# USB wiring   
```
ESP32-S2/S3 BOARD          USB CONNECTOR
                           +--+
    [  5V   ]    --------> | || VCC
    [GPIO 19]    --------> | || D-
    [GPIO 20]    --------> | || D+
    [  GND  ]    --------> | || GND
                           +--+
```

# USB hot socket
There are times when it works correctly and times when it doesn't.   
It works more stably if you connect before starting the firmware.   
When it works correctly, a log like this will be displayed.   
```
I (796) usb_hid: hid_host_device_callback
I (796) usb_hid: HID Device, protocol 'KEYBOARD' CONNECTED
I (806) usb_hid: hid_host_device_callback
I (806) usb_events: event_flags=0x0
I (816) usb_hid: HID Device, protocol 'NONE' CONNECTED
I (816) usb_events: event_flags=0x0
```


# Using USB-HUB
I tried it, but it doesn't work properly via USB-HUB.
