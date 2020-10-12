# DigiTron - A Digital Scantron System
A custom made Arduino board with a fully self-designed and soldered PCB. Has a lot of additional on board sensors and outputs that the normal arduino does not have, including an Accelerometer, a Gyroscope, a potentiometer, a photoresistor, an OLED display, an ultrasonic sensor, a microphone, a buzzer, 4 LEDs, and two General Purpose Buttons. All the necessary sketching, wiring, and soldering for each of these components was done by myself.

# Purpose
* There are two types of devices
    * Student Device
    * Teacher Device
* Students complete the multiple choice questions on their own devices
* Teacher devices allow them to set up test sizes, marking schemes, learning points, and many other things
* Most importantly, through an algorithm, it is able to provide general feedback on weak students, by measuring their question lengths, and students who may be involved in cheating

# How I Built It
* An Arduino for both the student and teacher devices
* Student information is displayed on a small OLED Display
* Teacher information is displayed on their computers when their device is connected to a Computer
* Devices communicate using the nRF24L01 radio module
* Software for computer written in Visual Studio, in Visual Basic

# Challenges & Issues
* Getting the Radio modules to talk to each other at considerable speeds
* Communicating the Arduino with the Computer Software
