# MouseDemo for SSD1306
Demo of moving a circle using the mouse.   
The circle moves when you move the mouse.   
I used [this](https://components.espressif.com/components/espressif/usb_host_hid/) component.   

# Hardware requirements

- ESP32S2/S3   
 These have USB-HOST functionality.

- USB Connector   
 I used this:
 ![usb-conector](https://github.com/user-attachments/assets/a8fb5313-54f6-422a-98de-5f4aff8c94b7)

- USB mouse   
 2-button or 3-button usb mouse.   
 Button 3 is not used in this project.   

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

# How to Use   
The circle moves when you move the mouse.
![usb-mouse-3](https://github.com/user-attachments/assets/020e0f71-aff5-4e12-8fad-1dc724336f2e)

Invert with left mouse click.   
![usb-mouse-2](https://github.com/user-attachments/assets/28ec7de7-d741-408a-8ed6-6821277129c7)


Right click the mouse to go back.   
![usb-mouse-1](https://github.com/user-attachments/assets/b8d152c5-2aed-450b-9f18-721f051c0b23)


