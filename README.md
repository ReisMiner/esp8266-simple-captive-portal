# esp8266-simple-captive-portal
Simple Captive Portal for the ESP8266 which is also used in the NodeMCUs for example!

## How to install?
### Method #1
- Download and install platformio CLI (also set shell variables)
- Build in the IDE of your choice i guess.

Honestly i have no idea how it's supposed to work that way, so just use the **Method #2** descirbed below.

### Method #2
This involves the arduino IDE, so go download and install it.
- Rename the *src* folder to *main*
- rename *main.cpp* to *main.ino*
- open the file in the arduino IDE
- go to file -> preferences and enter this url ``http://arduino.esp8266.com/stable/package_esp8266com_index.json`` where it says "additional board manager URLS"
- go to Tools-> Board: -> Bord Manager and install the ESP8266 board. Then Select your specific model under Tools -> Board -> ESP8266
- Flash
- Enjoy

## Configuration
Coming Soon (probably)

---
Made by ReisMiner#1111
