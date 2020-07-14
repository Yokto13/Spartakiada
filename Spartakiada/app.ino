// Prep for the whole app.
// It is preferable to have externders for motors and seperate externders for buttons.
#include <SoftwareI2C.h>

// We need 100 pins for buttons and 100 for motors.
// If we decide to go for 'only externders' version, we will need: 2 * ceil(100/8) = 26
// Alternatively it should be also feasible to go for 24 etenders 12/12 for buttons/motors,
// the rest migh be done with standart GPIO pins. In that case we need total of 8 pin which is ok.
// The last possibility is to use 25 extenders, in that case one is for both input/output.
// For consistency: whenever an adress or a pin layout is written its in the hex notation.


// Those are i2c channels we can commuicate on.
// The corresponding sda, scl pins are set in setup.
// The penultimate char is a letter: M for motors, B buttons MB may be added later for motor/buttons.
// The last is just an index.
SoftwareI2C WireM1; // First i2c communaction channel, others will folow :)
SoftwareI2C WireB1;
// ! It is assumed that adresses of M1 and B1 will be the same. 
// !This is likely though if it isn't the case it won't work.
uint8_t adresses1[] = {0x21};

/**
* * Sets pins according to the binary representation of [layout].
  @param layout uint8_t To be set on pins.
  @param wire pointer to instance of the given channel.
  @param adress uint8_t, specifies the divice adress.
*/ 
void set_pins(uint8_t layout, SoftwareI2C *wire, uint8_t adress)
{
  wire->beginTransmission(adress);
  wire->write(layout);
  wire->endTransmission();
}


uint8_t read_pins(SoftwareI2C *wire, uint8_t adress)
{
  uint8_t c = 0;
  wire->requestFrom(adress, 1);
  if(wire->available())    // slave may send less than requested
  {
    c = wire->read();    // receive a byte as character
  }
  return c;
}


// TODO
void set_all_motors_down()
{
  // Activate all motors.
  // Constantly check for buttons ON.
  // When this happens turn the corresponding motor of.
  for(uint8_t adress: adresses1)
  {
    set_pins(0xFF, &WireM1, adress); 
  }

  for(uint8_t adress: adresses1)
  {
    uint8_t response = read_pins(&WireB1, adress); 
    if(response > 0)
    {
      set_pins(~response, &WireM1, adress);
    }
  }
}

void copy_buttons()
{
  // Copies the information from buttons to motors.

  for(uint8_t adress: adresses1)
  {
    uint8_t response = read_pins(&WireB1, adress);
    Serial.println(response); 
    set_pins(response, &WireM1, adress);
  }
}


void setup()
{
  Serial.begin(115200);
  Serial.println("Serial opened sucessfuly!");

  WireM1.begin(3, 2); // SDA, SCL
  WireB1.begin(12,13);
  // TODO do this for all extenders:
  for(uint8_t adress: adresses1)
  {
    set_pins(0x0, &WireM1, adress); // This is here so we know what we should except on the given extender 
    set_pins(0x0, &WireB1, adress);
  }
  Serial.println("Setup finished.");
  delay(5000);
}
int c = 1;
// TODO pretty much the whole loop.
void loop()
{
  copy_buttons();
  Serial.println("Copied.");
  set_pins(c, &WireM1, 0x20);
  c = c << 1;
  if(c == 16) c=1;
  delay(500);
   // Nejaka ta sestava
   // Kdyz umime detekovat, kdy je motor dole, muzeme sestavy zadavat jako pocet otoceni
   // Popripade muzeme zadavat casy, za jak dlouho se ma co pustit.
}