This project is a configurable desk lighting system using an ESP8266 microcontroller.
It allows users to choose and customize various lighting effects via a web interface and physical buttons,
with status displayed on an OLED screen.

Project Setup:
1) Clone the Repository:
Download or clone this repository to your local machine.

2)Circuit Assembly:
Connect the components as follows:
OLED Display (I2C):
SDA -> ESP8266 D2 (GPIO4)
SCL -> ESP8266 D1 (GPIO5)
VCC -> ESP8266 3V3
GND -> ESP8266 GND
LED 1:
Anode (+) -> Resistor (220-330 Ohm) -> ESP8266 D6 (GPIO12)
Cathode (-) -> ESP8266 GND
LED 2:
Anode (+) -> Resistor (220-330 Ohm) -> ESP8266 D7 (GPIO13)
Cathode (-) -> ESP8266 GND
LED 3:
Anode (+) -> Resistor (220-330 Ohm) -> ESP8266 D5 (GPIO14)
Cathode (-) -> ESP8266 GND
Button 1 (Change Effect):
One terminal -> ESP8266 D3 (GPIO0)
Other terminal -> ESP8266 GND
Button 2 (Change Parameter/Speed):
One terminal -> ESP8266 D4 (GPIO2)
Other terminal -> ESP8266 GND

3)Upload the Sketch:
Upload the sketch located in the ESP8266_LED_FX_Web_Modular folder (the .ino file and its accompanying .h and .cpp files)
to your ESP8266 board using the Arduino IDE or a compatible programmer. Ensure you have configured your Wi-Fi credentials in the config.h file.

