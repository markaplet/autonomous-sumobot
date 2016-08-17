# Autonomous Sumobot v1.0

_**Disclaimer:** I have never written C or C++ before. I am learning as I go. The code contained within this repository is my first attempt at creating a totally autonomous robot for the [Sacramento MakerHQ RoboSumo](http://www.makerhq.org/robosumo) competition using a wooden [Sumobot JR chassis](https://github.com/makenai/sumobot-jr). Many of the test are ripped straight from the Arduino education pages, or from the library developers and modified for my usage._

## Sensors

* SparkFun Line Sensor - [QRE1113](https://www.sparkfun.com/products/9453)
* Ultrasonic Distance Sensor - [HC-SR04](https://www.amazon.com/SainSmart-HC-SR04-Ranging-Detector-Distance/dp/B004U8TOE6)
* Infrared [Receiver](https://www.amazon.com/gp/product/B00EFOQEUM/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1)

## Boards

* [SainSmart UNO R3](http://www.sainsmart.com/sainsmart-uno-r3-atmega328-au-development-board-compatible-with-arduino-uno-r3.html)
* [Adafruit Motor Shield v1.2](https://www.adafruit.com/products/81)

## Wiring Pins

* M1 = Left Motor
* M2 = Right Motor
* 10 (Servo 1 on shield) = Ultrasonic Trigger
* 9 (Servo 2 on shield) = Ultrasonic Echo
* A0 = IR Remote receiver
* A4 = Front Left Edge Sensor
* A5 = Front Right Edge Sensor
* A3 = Rear Edge Sensor (Reserved)

## General Concepts

* Bot does not attack until remote key is pressed.
* When remote key is pressed, bot will begin 5 second countdown
* Bot will attempt to seek out opponent using ultrasonic sensors
* If opponent is found, bot will charge
* If edge is detected, bot will backup, rotate away from edge, and continue looking for opponent

## Issues

* NewPing & IRremote libraries both use "timer 2" function and compiler throws a *vector_7* error on compilation. I modified *NewPing.h* library to disable the TIMMER_ENABLED value on line 153 by setting it to false.
* Had to use small delay() functions in main loop to prevent motors from stuttering.
* Still Using delay() instead of mills
* Bot will not always react soon enough to edge of arena
