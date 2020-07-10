#include "Arduino.h"
#include "PCF8574.h"

// Set i2c address
PCF8574 pcf(0x20);

int SensorInputs[4];


void setup()
{
  Serial.begin(9600);
  Serial.println("Serial inited");

  pinMode(5, OUTPUT);

  digitalWrite(5, HIGH);

  for(int i = 0; i < 4; ++i)
    pcf.pinMode(i, INPUT);
  for(int i = 4; i < 8; ++i)
    pcf.pinMode(i, OUTPUT);
}

void loop()
{
  for(int i = 0; i < 4; ++i)
  {
    Serial.println(pcf.digitalRead(i));
    if(pcf.digitalRead(i) == HIGH)
      pcf.digitalWrite(i+4, HIGH);
    else
      pcf.digitalWrite(i+4, LOW);    
  }
  delay(1000);
  Serial.println("======================");
}
