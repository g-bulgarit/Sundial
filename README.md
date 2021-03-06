# Sundial
Wake up to a sunrise in your bedroom.
______________________


## Current Status:
Currently, the project is based mostly off of the free Blynk framework, that take care of the connectivity, the RTC and even the alarm component.

The RGB adressable leds are being controlled by the wonderful FastLED library. This code is mostly an integration of the exisiting components into a working device.

The set alarms are stored in EEPROM so if the device shuts down and boots back up, the alarm time will not be lost.

## Required Hardware
* A strip of WSB2182 adressable leds.
* An ESP8266 controller board, I used a Wemos D1 Mini, although it may be wise to use a different board that does not have hardware timer clashes with literally everything.
* A power supply rated for the LED voltage and max current draw, for me it's a maximum of 60 mA per led, so the ideal power supply should be something in the lines of:

    PSU Max Current: ((60mA)*(LED amount)) * **1.25**

    Where the 1.25 term is a safety coefficient.

## Next Goals (if time permits)
* Write a companion app that fetches the alarms from my phone to allow seamless integration without having to set the alarm in the Blynk app every time.