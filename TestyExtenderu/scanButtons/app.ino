#include <SoftwareI2C.h>

// Test that motors and buttons work..


SoftwareI2C Wire1;
SoftwareI2C Wire2;

uint8_t Adresses[] = {0x20, 0x21, 0x22, 0x23};

// Sets everything up
// Motors should all be low
// Buttons high so we can than detect buttons with zeros.
void setup() 
{
  Serial.begin(115200);
  Wire1.begin(2, 3); // sda, scl
  Wire2.begin(4, 5);

  
  Wire1.beginTransmission(0x20); // 32
  Wire1.write(0x0);
  Wire1.endTransmission();

  Wire1.beginTransmission(0x21); // 33
  Wire1.write(0x0);
  Wire1.endTransmission();

  Wire1.beginTransmission(0x22);
  Wire1.write(0x0);
  Wire1.endTransmission();

  Wire1.beginTransmission(0x23);
  Wire1.write(0x0);
  Wire1.endTransmission();

  //Serial.println("1 on pins");

  Wire2.beginTransmission(0x0);
  Wire2.write(0xFF);
  Wire2.endTransmission();

  Wire2.beginTransmission(0x21);
  Wire2.write(0xFF);
  Wire2.endTransmission();

  Wire2.beginTransmission(0x22);
  Wire2.write(0xFF);
  Wire2.endTransmission();

  Wire2.beginTransmission(0x23);
  Wire2.write(0xFF);
  Wire2.endTransmission();
  delay(3000);
}

void check_motor(uint8_t adress, uint8_t layout)
{
  Wire1.beginTransmission(adress);
  Wire1.write(layout);
  Wire1.endTransmission();
  int time_from_start = 0;
  bool should_exit = false;
  while (time_from_start < 20000)
  {
    byte mem[4]; 
    for(int j = 0; j < 4; ++j)
    {
      byte adress = Adresses[j];
      Wire2.requestFrom(adress, 1);
      while(Wire2.available())    // slave may send less than requested
      {
        mem[j] = Wire2.read();    // receive a byte as character
      }
    }
    for(int j = 0; j < 4; ++j)
    {
      uint8_t adress = Adresses[j];
      Wire2.requestFrom(adress, 1);
      while(Wire2.available())    // slave may send less than requested
      {
        byte c = Wire2.read();    // receive a byte as character
        byte b = mem[j];
        if(c != b)
        {
          for(int i = 7; i >= 0; --i)
          {
            int bit1 = c&1;
            int bit2 = b&1;
            if(bit1 != bit2)
            {
              Serial.print("1 detected at pin: ");
              Serial.println(i);
              Serial.print("Adress:");
              Serial.println(adress);
              Serial.println("--------------");
              should_exit = true;
              break;
            }
            c = c >> 1;
            b = b >> 1;
          }
        }
        if(should_exit)
          break;
      }
      delay(10);
      time_from_start += 10;
    }
    if(should_exit)
      break;
  }
  Wire1.beginTransmission(adress);
  Wire1.write(0x0);
  Wire1.endTransmission();
}

void loop()
{
  uint8_t layout = 0x1;
  for(int i = 0; i < 8; ++i)
  {

    for(uint8_t adress : Adresses)
    {
      Serial.print("Layout: ");
      Serial.println(i);
      Serial.print("Adress:");
      Serial.println(adress);
      check_motor(adress, layout);
      delay(100);
    }
    layout = layout<<1;
  }
}