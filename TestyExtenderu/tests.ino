/****************************************************************
 *                 TESTS FOR PCF 8574 EXTENDER.                 *
 *               ASSUMES THAT THE ADRESS IS 0X20                *
 *   HOWEVER, THIS CAN BE EASILY CHANGED IN THE DECLARATION.    *
 * THIS TESTS ARE INTENDED TO TEST SOME OF ITS BASIC FUNCTIONS. *
 *     EACH TEST HAS A DESCRIPTION ABOUT WHAT IT SHOULD DO.     *
 *                        DOMINIK FARHAN                        *
 *                          JULY 2020                           *
 ****************************************************************/
#include "Arduino.h"
#include "PCF8574.h"

// Set i2c address
PCF8574 pcf(0x20);


// Every 3 seconds alters between 1/0 on pin P3 and GPIO 4 on Arduino for LED.
/*
void setup()
{
  Serial.begin(9600);
  Serial.println("Serial inited");

  pinMode(4, OUTPUT);

  pcf.pinMode(3, OUTPUT);
}

void loop()
{
  pcf.digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  Serial.println("HIGH");
  delay(3000);
  pcf.digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  Serial.println("LOW");
  delay(3000);
}*/



// Check for signal on P6.
/*
void setup()
{
  Serial.begin(115200);
  Serial.println("Serial inited");

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  pcf.pinMode(6, INPUT);
}

void loop()
{
  if(pcf.digitalRead(6) == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");
  
  delay(10);
}*/

// Put 1 on P2 when there is 1 at P5.
// Basically combination of the two previous examples.
/*
void setup()
{
  Serial.begin(115200);
  Serial.println("Serial inited");

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  pcf.pinMode(2, OUTPUT);
  pcf.pinMode(5, INPUT);
}

void loop()
{
  if(pcf.digitalRead(5) == HIGH)
  {
    pcf.digitalWrite(2, HIGH);
    Serial.println("HIGH");
  }
  else
  {
    pcf.digitalWrite(2, LOW);
    Serial.println("LOW");
  }
  
  delay(10);
}*/


// Even pins are INPUTs, odd OUTPUTS.
// 1 on an even pin will result in 1 on pin with number even+1.
void setup()
{
  Serial.begin(115200);
  Serial.println("Serial inited");

  pinMode(4, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(7, HIGH);


  for(int i = 0; i<8; ++i)
  {
    Serial.println(i);
    if(i % 2 == 0)
      pcf.pinMode(i, INPUT);
    else
      pcf.pinMode(i, OUTPUT);
    delay(1000); 
  }
  delay(3000);
}

void loop()
{
  for(int i = 1; i < 8; i+=2)
  {
    if(pcf.digitalRead(i-1) == HIGH)
    {
      pcf.digitalWrite(i, HIGH);
      Serial.print("Output was set on HIGH on pin ");
      Serial.println(i);
    }
    else
    {
      pcf.digitalWrite(i, LOW);
      Serial.print("Output was set on LOW on pin ");
      Serial.println(i);
    }
    delay(100);
  }
  
  delay(10);
}
