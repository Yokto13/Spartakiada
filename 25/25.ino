// Prep for the whole app.
// It is preferable to have extenders for motors and seperate extenders for buttons.
#include <SoftwareI2C.h>

// We need 100 pins for buttons and 100 for motors.
// If we decide to go for 'only extenders' version, we will need: 2 * ceil(100/8) = 26
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
// ! This is likely though if it isn't the case it won't work.
uint8_t adresses1[] = {0x20, 0x21, 0x22, 0x23};

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

void set_all_high(SoftwareI2C *wire, uint8_t adress)
{
  set_pins(0xFF, wire, adress);
}

void set_all_low(SoftwareI2C *wire, uint8_t adress)
{
  set_pins(0x0, wire, adress);
}


/**
 * * Given a pointer to wire and adress, reads the corresponding extender and returns a 8 bit number.
 * * Bits of the returned number represente the layout on the extender.
 * 
 * @param wire: pointer to SoftwareI2C object
 * @param adress, uint8_t, adress of an extender that can be found on this wire.
*/
uint8_t read_pins(SoftwareI2C *wire, uint8_t adress)
{
  uint8_t c = 0;
  wire->requestFrom(adress, 1);
  if(wire->available())    
    c = wire->read();

  return c;
}


// TODO
void set_all_motors_down()
{
  // Activate all motors.
  // Constantly check for buttons ON.
  // When this happens turn the corresponding motor of.
  uint8_t response = 0;
  int delay_lenght = 30; // ms
  int wait_for_motors = 24; // s
  int from_start = 0;
  for(uint8_t adress: adresses1)
    set_all_high(&WireM1, adress);

  // TODO rewrite for more wires 
  bool all_buttons_high = false;
  while (!all_buttons_high)
  {
    all_buttons_high = true;
    for(uint8_t adress: adresses1)
    {
      response = read_pins(&WireB1, adress); 
      if(response > 0)
        set_pins(~response, &WireM1, adress);
      if(response != 255)
        all_buttons_high = false;
    }
    delay(delay_lenght);
    from_start += delay_lenght;
    if(from_start/1000 > wait_for_motors)
      break;
  }
}


/**
 * * Rotates all motors till the corresponding button fires.
 * * Note that this dosen't mean motors will move exactly 360 deg.
 * * If they are starting from down pos it will be approx 360 deg.
 * * Otherwise they will just turn until the button is pushed.
 * It might be a good idea to turn all motors down with [set_all_motors_down()]
 * before calling this function.
 * ! This function won't end if all buttons aren't fireing.
 * TODO solve the problem on the previous line.
*/
void all_do_one_cycle()
{
  for(uint8_t adress:adresses1)
    set_all_high(&WireM1, adress);
  
  // TODO other motors
  // Wait, otherwise if all were set down, buttons would fire
  delay(3000);
  for(uint8_t adress: adresses1)
  {
    uint8_t response = read_pins(&WireB1, adress); 
    if(response > 0)
      set_pins(~response, &WireM1, adress);
  }
}


/**
 * * Does the given number of cycles with all motors.
 * 
 * @param number_of_cycles: int, number of cycles to do
 * @param start_down: bool, default to false, if true [set_all_motors_down()] called at the start.
*/
void all_do_cycles(int number_of_cycles, bool start_down = false)
{
  if (start_down)
    set_all_motors_down();
  
  for(int i = 0; i < number_of_cycles; ++i)
    all_do_one_cycle();  
}


/**
 * * Reads bits from buttons and sets the same layouts to the motors.
*/
void copy_buttons_to_motors()
{
  for(uint8_t adress: adresses1)
  {
    uint8_t response = read_pins(&WireB1, adress);
    Serial.println(response); 
    set_pins(response, &WireM1, adress);
  }
}


void even_do_cycles(int number_of_cycles, bool start_down = false)
{
    if (start_down)
      set_all_motors_down();
    
  for(int i = 0; i < number_of_cycles; ++i)
    even_do_one_cycle();
}


void even_do_cycle()
{
  for(uint8_t adress:adresses1)
      set_pin(0x55,&WireM1, adress);
  
  // TODO other motors
  // Wait, otherwise if all were set down, buttons would fire
  delay(3000);
  for(uint8_t adress: adresses1)
  {
    uint8_t response = read_pins(&WireB1, adress);
    if(response > 0)
    {
      // Because of this only motors with unpushed buttons (0) will work.
      response = ~response
      // Gets rid of odd motors.
      response = response & 0xAA;
      set_pins(response, &WireM1, adress);
    }
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
    set_all_low(&WireM1, adress); // Everything is set down so we know what to expect on extenders
    set_all_low(&WireB1, adress);
  }

  Serial.println("Setup finished.");
  delay(5000);
}
int c = 1;
// TODO pretty much the whole loop.
void loop()
{
  Serial.println("Sestavicka se vsema zacina!")
  all_do_cycles(2, start_down=true);
  Serial.println("Sestavicka se vsema skoncila");
  delay(10000);
  Serial.println("Sestavicka se sudymi zacina");
  
  delay(10000);
   // Nejaka ta sestava
   // Kdyz umime detekovat, kdy je motor dole, muzeme sestavy zadavat jako pocet otoceni
   // Popripade muzeme zadavat casy, za jak dlouho se ma co pustit.
}