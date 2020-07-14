#include <SoftwareI2C.h>


#define ADR (0x20)
// Ports are changable because of SoftwareI2C
#define SDA 3
#define SCL 2
 
#include "SoftwareI2C.h"
SoftwareI2C WireS;

/*
// Blink on pin 2.
void setup() 
{
  Serial.begin(115200);
  WireS.begin(SDA, SCL); // sda, scl
}
 
void loop() 
{
  WireS.beginTransmission(ADR);
  WireS.write(0x2);
  WireS.endTransmission();
  Serial.println("1 on pin 1");
  delay(5000);
  WireS.beginTransmission(ADR);
  WireS.write(0x0);
  WireS.endTransmission();
  Serial.println("0 on pin 1");
  delay(5000);
}*/

// Read all pins.
void setup() 
{
  Serial.begin(115200);
  WireS.begin(SDA, SCL); // sda, scl

  WireS.beginTransmission(ADR);
  WireS.write(0xAA); // 10101010
  WireS.endTransmission();
}
/* OOOLD school comment */
/* Just for fun ;)*/
void loop() 
{
  WireS.requestFrom(ADR, 1);
  while(WireS.available())    // slave may send less than requested
  {
    byte c = WireS.read();    // receive a byte as character
    Serial.println(c);
    while(c>0)
    {
      Serial.print(c&1);
      c = c >> 1;
    }
  }
  Serial.println();

  delay(500);
}
