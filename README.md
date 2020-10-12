# DigiTron - A Digital Scantron System (Hack The Hammer II) (Second Place)
A custom made Arduino board with a fully self-designed and soldered PCB. Has a lot of additional on board sensors and outputs that the normal arduino does not have, including an Accelerometer, a Gyroscope, a potentiometer, a photoresistor, an OLED display, an ultrasonic sensor, a microphone, a buzzer, 4 LEDs, and two General Purpose Buttons. All the necessary sketching, wiring, and soldering for each of these components was done by myself.

# Purpose
I wasn't a big fan of the original Arduino board, with its limited ground pins and stricly female pins and almost no onboard sensors/outputs, so I decided to learn how to make my own PCB and make my own Arduino!

# Issues
I had a LOT of trouble getting the bootloader onto the ATMEGA328P Chip. This is because for the two capacitors that go to the crystal clock chip, I had mistakenly put on 22uF capacitors instead of 22pF capacitors. This lead to weeks of troubleshooting and getting very confused. Luckily, I looked back at my schematic and found my issue within a few weeks, and the board worked perfectly!
