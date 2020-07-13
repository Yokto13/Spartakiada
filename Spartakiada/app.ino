// Prep for the app.

#include <assert.h>
#include <string.h>

#include "Arduino.h"
#include "PCF8574.h"


PCF8574 pcf(0x20);
String Buffer;

void setup()
{
  Serial.begin(115200);
  Serial.println("Serial started.");

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);

  for(int i = 0; i <4; ++i)
    pcf.pinMode(i, OUTPUT);
}

void loop()
{
  /*
  while(Serial.available()>0)
  {
    Buffer = Serial.readString();
    int command, pin, highLow;
    command = Buffer.toInt();
    Serial.print(command);
    Serial.println(" was read from Serial input...");
    pin = command / 10;
    highLow = (command % 10 == 1) ? HIGH:LOW;
    pcf.digitalWrite(pin, highLow);
    delay(100);
  }
  */
  int previous;
  for(int i = 0; i < 4; ++i)
  {
    previous = (i==0) ? 3:i-1;
    pcf.digitalWrite(i, HIGH);
    pcf.digitalWrite(previous, LOW);
    Serial.print(i+1);
    Serial.println(" should be HIGH.");
    delay(5000);
  }
}


