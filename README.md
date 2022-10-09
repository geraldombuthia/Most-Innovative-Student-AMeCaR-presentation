# AMeCaR Presentation for the Most Innovative Student Award Category

This repo contains the firmware software for the Actuation and control systems for the AMeCaR project.
It contains software for the Wi-Fi control using an ESP8266 and the Servo and Motor actuation software on an Arduino Mega.

## Wi-Fi Control

This control is achieved by utilising an ESP8266 running a web server and a Wi-Fi device gets to access the website interface with the IP address of the ESP8266. It is important that both the ESP and the controlling device be connected to the same network.

## Motor and Servo Control.

This is achieved by sending control signals from the ESp8266 as digital Highs and Lows. The arduino mega reads the respective pin signals and if high controls the motor appropriately. This is an easy control mechanism. However alot of pins are required.