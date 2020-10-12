# DigiTron - A Digital Scantron System
A custom made Arduino board with a fully self-designed and soldered PCB. Has a lot of additional on board sensors and outputs that the normal arduino does not have, including an Accelerometer, a Gyroscope, a potentiometer, a photoresistor, an OLED display, an ultrasonic sensor, a microphone, a buzzer, 4 LEDs, and two General Purpose Buttons. All the necessary sketching, wiring, and soldering for each of these components was done by myself.

# Purpose
* There are two types of devices
    * Student Device
    * Teacher Device
* Students complete the multiple choice questions on their own devices
* Teacher devices allow them to set up test sizes, marking schemes, learning points, and many other things
* Most importantly, through an algorithm, it is able to provide general feedback on weak students, by measuring their question lengths, and students who may be involved in cheating

# Issues
I had a LOT of trouble getting the bootloader onto the ATMEGA328P Chip. This is because for the two capacitors that go to the crystal clock chip, I had mistakenly put on 22uF capacitors instead of 22pF capacitors. This lead to weeks of troubleshooting and getting very confused. Luckily, I looked back at my schematic and found my issue within a few weeks, and the board worked perfectly!
