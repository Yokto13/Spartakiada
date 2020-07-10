/*
#include "Arduino.h"
#include "PCF8574.h"

// Set i2c address
PCF8574 pcf8574(0x20);


void setup()
{
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pcf8574.pinMode(P1, OUTPUT);
  pcf8574.pinMode(P2, OUTPUT);
  pcf8574.pinMode(P3, OUTPUT);
  pcf8574.pinMode(P5, OUTPUT);
  pcf8574.pinMode(P4, OUTPUT);

  pcf8574.pinMode(P6, INPUT);

  pcf8574.digitalWrite(P1, LOW);
  pcf8574.digitalWrite(P2, LOW);
}

void loop()
{
  Serial.println("Spinac je: ");
  int sensor = pcf8574.digitalRead(P6);
  Serial.println(sensor);
  delay(2000);
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  pcf8574.digitalWrite(P3, LOW);
  pcf8574.digitalWrite(P5, HIGH);
  pcf8574.digitalWrite(P4, LOW);
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  pcf8574.digitalWrite(P3, HIGH);
  pcf8574.digitalWrite(P5, LOW);
  pcf8574.digitalWrite(P4, HIGH);
  delay(1000); 
}*/

/*
#include "Arduino.h"
#include "PCF8574.h"

#define N_OF_EXTENDERS 1

int Adresses[N_OF_EXTENDERS] = {0x20}; 

PCF8574 Extenders[N_OF_EXTENDERS] = {PCF8574(0x20)};

int SensorInputs[N_OF_EXTENDERS][4];


void setup()
{
  Serial.begin(9600);
  Serial.println("Serial inited");
  /*
  for(int i = 0; i < N_OF_EXTENDERS; ++i)
  {
    PCF8574 ex(Adresses[i]);
    Extenders[i] = ex;
  }*/

  // Assume that we want to init all 8 pins
  // First four are for input the second four for output.
  for(int i = 0; i < N_OF_EXTENDERS; ++i)
  {
    for(int j = 0; j < 4; ++j)
      Extenders[i].pinMode(j,INPUT);
    for(int j = 4; j < 8; ++j)
      Extenders[i].pinMode(j,OUTPUT);
  }
  Serial.println("Setup finnished.");
}

void loop()
{
  for (int i = 0; i < N_OF_EXTENDERS; ++i)
  {
    for(int j = 0; j < 4; ++j)
    {
      SensorInputs[i][j] = Extenders[i].digitalRead(j);
      Serial.println(SensorInputs[i][j]);
    }
  }

  for (int i = 0; i < N_OF_EXTENDERS; ++i)
  {
    for(int j = 4; j < 8; ++j)
    {
      if(SensorInputs[i][j-4] == HIGH)
      {
        Extenders[i].digitalWrite(j, HIGH);
        Serial.println("Je to high!!");
      }
      else
      {
        Serial.println("Je to low");
        Extenders[i].digitalWrite(j, LOW);
      }
    }
  }
  delay(10000);
  Serial.println("--------------");
  /*
  Extenders[0].digitalWrite(P5, HIGH);
  Serial.println("H");
  delay(5000);
  Extenders[0].digitalWrite(P5, LOW);
  Serial.println("L");
  delay(5000);
  */
  /*
  Serial.println("Spinac je: ");
  int sensor = pcf8574.digitalRead(P6);
  Serial.println(sensor);
  delay(2000);
  digitalWrite(2, HIGH);   // turn the LED on (HIGH is the voltage level)
  pcf8574.digitalWrite(P3, LOW);
  pcf8574.digitalWrite(P5, HIGH);
  pcf8574.digitalWrite(P4, LOW);
  delay(1000);                       // wait for a second
  digitalWrite(2, LOW);    // turn the LED off by making the voltage LOW
  pcf8574.digitalWrite(P3, HIGH);
  pcf8574.digitalWrite(P5, LOW);
  pcf8574.digitalWrite(P4, HIGH);
  delay(1000);*/
}

