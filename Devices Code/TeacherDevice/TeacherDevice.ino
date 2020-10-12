#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>


struct CONNECTION_PACKAGE
{
  char code[5];
  char studentFirstName[10];
  char studentLastName[10];
  int studentId;
};

struct TEST_INFO_PACKAGE
{
  int duration;
  int numQuestions;
};


RF24 radio(7,8);
const byte address[6] = "00011";
const byte addressd[6] = "00111";
CONNECTION_PACKAGE data;
TEST_INFO_PACKAGE testInfo;
String code = "ABCD";
int numConnected = 0;

void setup() {
  Serial.begin(9600);
  
  testInfo.duration = 60;
  testInfo.numQuestions = 4;
  
  radio.begin();
  radio.openReadingPipe(1, address);
  radio.openWritingPipe(addressd);
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_2MBPS);
  radio.startListening();
}


void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    Serial.println(data.code);
    Serial.println(data.studentId);
    if(data.code[0] == code.charAt(0) && data.code[1] == code.charAt(1) && data.code[2] == code.charAt(2) && data.code[3] == code.charAt(3))
    {
      numConnected++;
      Serial.println("OK!");
      radio.stopListening();
      delay(300);
      radio.write(&testInfo, sizeof(testInfo));
      radio.startListening();
    }
  }

  if(Serial.available())
  {
    Serial.read();
    radio.stopListening();
    boolean startTest = true;
    for(int i = 0; i < numConnected; i++) 
    {
      radio.write(&startTest, sizeof(boolean));
      delay(20);
    }
    radio.startListening();
  }
}
