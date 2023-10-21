# ACM x SHPE Embedded Workshop
## This workshop will be split into 3 parts:
1. Intro to ESP32 GPIO and Hardware Timers 
2. ESP32 Sensor Data over I2C and UART
3. ESP32 Sensor Data over Wifi

For this workshop we'll be using the ESP32 platform, developed by Espressif. The particular dev-board we'll be using is the ESP32-C3-DevKitM-1:

<img width="520" alt="image" src="https://github.com/Ucfacm/embedded_workshop/assets/112581413/6f0eb0c6-8dc5-48f5-9d4b-5df5b3b3108e">

The link to the Espressif docs page can be found [here](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/hw-reference/esp32c3/user-guide-devkitm-1.html)


For our software environment, we'll be using PlatformIO on vsCode:


<img width="220" alt="image" src="https://github.com/Ucfacm/embedded_workshop/assets/112581413/1f23ebd1-0aff-4ef3-81a6-545f27340743">


### Download vsCode [here](https://code.visualstudio.com/download)

<img width="220" alt="image" src="https://github.com/Ucfacm/embedded_workshop/assets/112581413/3315184f-d646-4920-a71b-bb98de3cef34">

### The setup for the PlatformIO IDE can be found [here](https://platformio.org/install/ide?install=vscode)

### ESP-IDF Framework
The code will be written using the ESP-IDF framework. For your reference, here are links to some of the API docs:
- [GPIO](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html)
- [High Resolution Timer](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/esp_timer.html#high-resolution-timer-esp-timer)
- [FreeRTOS](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html)
