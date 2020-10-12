
#include <SPI.h>
#include <Wire.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define BTN_PREV 11
#define BTN_A 10
#define BTN_B 9
#define BTN_C 8
#define BTN_D 7
#define BTN_E 6
#define BTN_NEXT 5

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

//Globals
Adafruit_SSD1306 display(128, 64, &Wire, 4);
RF24 radio(22, 23);

CONNECTION_PACKAGE connectPackage;
TEST_INFO_PACKAGE testInfo;
const byte address[6] = "00011";
const byte addressd[6] = "00111";
const String firstName = "Araad";
const String lastName = "Shams";
int testDuration;
int testNumQuestions;

void setup()
{
  Serial.begin(115200);

  radio.begin();
  radio.openReadingPipe(1, addressd);
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_2MBPS);
  radio.stopListening();

  pinMode(BTN_A, INPUT_PULLUP);
  pinMode(BTN_B, INPUT_PULLUP);
  pinMode(BTN_C, INPUT_PULLUP);
  pinMode(BTN_D, INPUT_PULLUP);
  pinMode(BTN_E, INPUT_PULLUP);
  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (true);
  }


  drawIntro();
  delay(2000);

  String code = getClassCode();
  showConnecting();

  while (!connectToTeacher(code))
  {
    showConnectionFailure();
    code = getClassCode();
    showConnecting();
  }

  showConnectionSuccess();
  delay(1000);

  waitForTestStart();



}


void loop() {
  Serial.println(waitButtonPressed());


}


void waitForTestStart()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(8, 0);

  display.println(F("Get Ready!"));

  display.setCursor(20, 20);
  display.setTextSize(2);
  String duration = "";
  String questionNums = "";
  testInfo.duration /= 60;
  for (int i = testInfo.duration; i < 100; i *= 10)
  {
    duration += " ";
  }

  for (int i = testInfo.numQuestions; i < 100; i *= 10)
  {
    questionNums += " ";
  }

  duration += testInfo.duration;
  questionNums += testInfo.numQuestions;

  display.println(questionNums);

  display.setCursor(20, 40);
  display.setTextSize(2);
  display.println(duration);

  display.setCursor(64, 23);
  display.setTextSize(1);
  if (testInfo.numQuestions > 1) display.println(F("Questions"));
  else display.println(F("Question"));

  display.setCursor(64, 43);
  display.setTextSize(1);

  if (testInfo.duration > 1) display.println(F("Minutes"));
  else display.println(F("Minute"));

  display.display();


  int startTheTest = startTest();

  while (startTheTest == 0)
  {
    startTheTest = startTest();
  }

  if (startTheTest == 1)
  {
    display.clearDisplay();
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(15, 25);
    display.println("START!");
    display.display();
  }


}

int startTest()
{
  radio.startListening();
  while (!radio.available());
  if (radio.available())
  {
    boolean receiveVal;
    radio.read(&receiveVal, sizeof(boolean));
    if (receiveVal) return 1;
    else if (!receiveVal) return 2;
    else return 0;
  }
  radio.stopListening();

}


void printButtonStatus()
{
  Serial.print("A:");
  Serial.print(!digitalRead(BTN_A));
  Serial.print("  B: ");
  Serial.print(!digitalRead(BTN_B));
  Serial.print("  C: ");
  Serial.print(!digitalRead(BTN_C));
  Serial.print("  D: ");
  Serial.print(!digitalRead(BTN_D));
  Serial.print("  E: ");
  Serial.print(!digitalRead(BTN_E));
  Serial.print("  PREV: ");
  Serial.print(!digitalRead(BTN_PREV));
  Serial.print("  NEXT: ");
  Serial.println(!digitalRead(BTN_NEXT));
}

void showConnecting()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(6, 0);

  display.println(F("Connecting"));
  display.fillCircle(50, 40, 3, WHITE);
  display.fillCircle(64, 40, 3, WHITE);
  display.fillCircle(78, 40, 3, WHITE);
  display.display();
}



boolean connectToTeacher(String code)
{
  code.toCharArray(connectPackage.code, 5);
  firstName.toCharArray(connectPackage.studentFirstName, firstName.length());
  lastName.toCharArray(connectPackage.studentLastName, firstName.length());
  connectPackage.studentId = 293;

  radio.write(&connectPackage, sizeof(connectPackage));
  delay(100);
  radio.startListening();
  long waitTime = millis();

  while (millis() - waitTime < 1000)
  {
    if (radio.available())
    {
      radio.read(&testInfo, sizeof(testInfo));
      Serial.println(testInfo.numQuestions);
      Serial.println(testInfo.duration);
      testDuration = testInfo.duration;
      testNumQuestions = testInfo.numQuestions;
      return true;
    }
  }
  radio.stopListening();
  return false;

}

void showConnectionSuccess()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12, 1);

  display.println(F("Connected"));
  for (int i = 50; i < 60; i++)
  {
    display.drawPixel(i, i - 8, WHITE);
    display.display();
    delay(15);
  }
  for (int i = 60; i > 35; i--)
  {
    display.drawPixel(120 - i, i - 8, WHITE);
    display.display();
    delay(2);
  }

}


void showConnectionFailure()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(12, 1);

  display.println(F("Bad Code!"));

  for (int i = 35; i < 60; i++)
  {
    display.drawPixel(i + 12, i - 8, WHITE);
    display.display();
    delay(2);
  }

  for (int i = 35; i < 60; i++)
  {
    display.drawPixel(108 - i, i - 8, WHITE);
    display.display();
    delay(2);
  }
  delay(1000);

}

void drawIntro()
{
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(2, 1);

  display.println(F("Welcome to"));

  display.setTextSize(3);
  display.setCursor(30, 17);

  display.println(F("digi"));

  display.setCursor(28, 42);

  display.println(F("Tron"));
  display.display();
}


String getClassCode()
{
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(17, 1);

  display.println(F("Enter Class Code"));
  display.drawLine(4, 50, 28, 50, WHITE);
  display.drawLine(36, 50, 60, 50, WHITE);
  display.drawLine(68, 50, 92, 50, WHITE);
  display.drawLine(100, 50, 124, 50, WHITE);
  display.display();

  int curPos = 1;
  String code = "";
  String next = "";
  int cursorMarks[] = {0, 9, 41, 73, 105};
  int indicatorCentres[] = {0, 16, 48, 80, 112};
  display.setTextSize(3);
  display.fillCircle(indicatorCentres[curPos], 55, 2, WHITE);
  display.display();

  while (code.length() < 5)
  {
    next = waitButtonPressed();
    if (next == "P")
    {
      if (curPos != 1)
      {
        display.fillCircle(indicatorCentres[curPos], 55, 2, BLACK);
        if (code.length() != 4) curPos--;
        else
        {
          display.setCursor(1, 55);
          display.setTextSize(1);
          display.setTextColor(BLACK);
          display.println("Press Next to Connect");
          display.setTextSize(3);
        }
        display.setCursor(cursorMarks[curPos], 27);
        display.fillCircle(indicatorCentres[curPos], 55, 2, WHITE);
        display.setTextColor(BLACK);
        display.println(code.charAt(code.length() - 1));
        display.setTextColor(WHITE);
        Serial.println(curPos);
        code = code.substring(0, code.length() - 1);
        Serial.println(code);
        display.setCursor(cursorMarks[curPos], 27);
      }
    }

    else if (next == "N")
    {
      if (code.length() == 4)
      {
        return code;
      }
    }

    else
    {
      if (code.length() != 4)
      {
        code += next;
        display.setCursor(cursorMarks[curPos], 27);
        display.println(next);
        display.fillCircle(indicatorCentres[curPos], 55, 2, BLACK);
        curPos++;
        if (curPos > 4)
        {
          curPos = 4;
          display.fillCircle(indicatorCentres[curPos], 55, 2, BLACK);
          display.setCursor(1, 55);
          display.setTextSize(1);
          display.println("Press Next to Connect");
          display.setTextSize(3);
        }
        else
        {
          display.fillCircle(indicatorCentres[curPos], 55, 2, WHITE);
        }
      }
    }

    display.display();
  }

}




String waitButtonPressed()
{
  while (digitalRead(BTN_A) && digitalRead(BTN_B) && digitalRead(BTN_C) && digitalRead(BTN_D) && digitalRead(BTN_E) && digitalRead(BTN_PREV) && digitalRead(BTN_NEXT));

  if (!digitalRead(BTN_A))
  {
    while (!digitalRead(BTN_A));
    return "A";
  }

  if (!digitalRead(BTN_B))
  {
    while (!digitalRead(BTN_B));
    return "B";
  }

  if (!digitalRead(BTN_C))
  {
    while (!digitalRead(BTN_C));
    return "C";
  }

  if (!digitalRead(BTN_D))
  {
    while (!digitalRead(BTN_D));
    return "D";
  }

  if (!digitalRead(BTN_E))
  {
    while (!digitalRead(BTN_E));
    return "E";
  }

  if (!digitalRead(BTN_PREV))
  {
    while (!digitalRead(BTN_PREV));
    return "P";
  }

  if (!digitalRead(BTN_NEXT))
  {
    while (!digitalRead(BTN_NEXT));
    return "N";
  }
}
