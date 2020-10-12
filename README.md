# DigiTron - A Digital Scantron System
Being a high school student myself, I have been using Scantrons for many years. Whereas they do make marking easier for the teachers relative to the native multiple choice question system, digiTron further simplifies this process by marking the tests as soon as the student is done! Students like me always have that feeling of doubt when changing their answer on a scantron, "What if it doesn't get erased fully? What if it reads my answer wrong?". And from personal experiences, I have ran into multiple situations where the scantron would mark my answer incorrectly! The digiTron completely eliminates this possibility of unsure as it is completely digital! Scantron paper is also quite pricey, whereas digiTron's are a one-time investment of only $7 per person! DigiTron will truly make school life better and easier for high-school students such as myself



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

![Student Device](Images/StudentDevice.png)
