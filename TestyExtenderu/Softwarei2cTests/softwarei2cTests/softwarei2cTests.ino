#include <SoftwareI2C.h>


#define ADR (0x20)
// Ports are changable because of SoftwareI2C
#define SDA 13
#define SCL 12
 
SoftwareI2C WireS;
//
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
/*
// Read all pins.
// The bin-number displayed should be the same as the one specified in 
// setup.
void setup() 
{
  Serial.begin(115200);
  WireS.begin(SDA, SCL); // sda, scl

  WireS.beginTransmission(ADR);
  WireS.write(0xAA); // 10101010
  WireS.endTransmission();
}
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
}*/


/*
// Reads pin 4 and sets the same value on pin 3.
void setup() 
{
  Serial.begin(115200);
  WireS.begin(SDA, SCL); // sda, scl

  WireS.beginTransmission(ADR);
  WireS.write(0); // Set pins to LOW.
  WireS.endTransmission();
  Serial.println("Setup completed.");
}
void loop() 
{
  WireS.requestFrom(ADR, 1);
  while(WireS.available())    // slave may send less than requested
  {
    byte c = WireS.read();    // receive a byte as character
    if (c >> 4 & 1)
    {
      WireS.beginTransmission(ADR);
      WireS.write(8);
      WireS.endTransmission();
      Serial.println("1 on pin 3");
    }
    else
    {
      WireS.beginTransmission(ADR);
      WireS.write(0);
      WireS.endTransmission();
      Serial.println("0 on pin 3");
    }    
  }

  delay(500);
}*/

/*
void setup() 
{
  Serial.begin(115200);
  WireS.begin(SDA, SCL); // sda, scl

  WireS.beginTransmission(ADR);
  WireS.write(0xFF); // 10101010
  WireS.endTransmission();
}
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
}*/


/*
// Blink all pins.
void setup() 
{
  Serial.begin(115200);
  WireS.begin(SDA, SCL); // sda, scl
}
 
void loop() 
{
  WireS.beginTransmission(ADR);
  WireS.write(0xFF);
  WireS.endTransmission();
  Serial.println("1 on pins");
  delay(5000);
  /*WireS.beginTransmission(ADR);
  WireS.write(0x0);
  WireS.endTransmission();
  Serial.println("0 on pins");
  delay(5000);
}*/


/*
// Test that motors and buttons work..
SoftwareI2C Wire1;
SoftwareI2C Wire2;
void setup() 
{
  Serial.begin(115200);
  Wire1.begin(2, 3); // sda, scl
  Wire2.begin(4, 5);

  uint8_t epic = 0x0;

  Wire1.beginTransmission(0x20);
  Wire1.write(0x0);
  Wire1.endTransmission();
  //Serial.println("1 on pins");

  Wire1.beginTransmission(0x21);
  Wire1.write(epic);
  Wire1.endTransmission();

  Wire1.beginTransmission(0x22);
  Wire1.write(0x0);
  Wire1.endTransmission();

  Wire1.beginTransmission(0x23);
  Wire1.write(epic);
  Wire1.endTransmission();


  // Buttons
  Wire2.beginTransmission(0x22);
  Wire2.write(0xFF);
  Wire2.endTransmission();

  Wire2.beginTransmission(0x23);
  Wire2.write(0xFF);
  Wire2.endTransmission();
  delay(3000);
}
 
void loop() 
{
  Serial.println("22:");
  Wire2.requestFrom(0x22, 1);
  while(Wire2.available())    // slave may send less than requested
  {
    byte c = Wire2.read();    // receive a byte as character
    Serial.println(c);
    byte number[8] = {0};
    for(int i = 0; i < 8; ++i)
    {
      number[i] = c&1;
      c = c >> 1;
    }
    for(int i = 7; i >= 0; --i)
      Serial.print(number[i]);
  }
  Serial.println();
  Serial.println("23:");
  delay(30);
  Wire2.requestFrom(0x23, 1);
  while(Wire2.available())    // slave may send less than requested
  {
    byte c = Wire2.read();    // receive a byte as character
    Serial.println(c);
    byte number[8] = {0};
    for(int i = 0; i < 8; ++i)
    {
      number[i] = c&1;
      c = c >> 1;
    }
    for(int i = 7; i >= 0; --i)
      Serial.print(number[i]);
  }
  Serial.println();
  Serial.println("----------------------");
  delay(1000);
}*/



SoftwareI2C Wire1;
void setup() 
{
  Serial.begin(115200);
  Wire1.begin(2, 3); // sda, scl

  uint8_t epic = 0x0;

  Wire1.beginTransmission(0x20);
  Wire1.write(epic);
  Wire1.endTransmission();
  //Serial.println("1 on pins");

  Wire1.beginTransmission(0x21);
  Wire1.write(epic);
  Wire1.endTransmission();

  Wire1.beginTransmission(0x22);
  Wire1.write(epic);
  Wire1.endTransmission();

  Wire1.beginTransmission(0x23);
  Wire1.write(epic);
  Wire1.endTransmission();
}

void set_one_extender(SoftwareI2C *wire, uint8_t layout, uint8_t adress, int d)
{
  wire->beginTransmission(adress);
  wire->write(layout);
  wire->endTransmission();
  delay(d);
  wire->beginTransmission(adress);
  wire->write(0x0);
  wire->endTransmission();
}
 
void loop() 
{
  int d = 30000;
  uint8_t c = 1;
  for(int i = 0; i< 8; ++i)
  {
    set_one_extender(&Wire1, c, 0x20, d);
    c = c << 1;
  }

  c = 1;
  for(int i = 0; i< 8; ++i)
  {
    set_one_extender(&Wire1, c, 0x21, d);
    c = c << 1;
  }

  c = 1;
  for(int i = 0; i< 8; ++i)
  {
    set_one_extender(&Wire1, c, 0x22, d);
    c = c << 1;
  }

  c = 1;
  for(int i = 0; i< 8; ++i)
  {
    set_one_extender(&Wire1, c, 0x23, d);
    c = c << 1;
  }
}
