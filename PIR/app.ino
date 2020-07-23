// Simple PIR example


int pirPin = 3;

void setup()
{
  Serial.begin(115200);

  pinMode(pirPin, INPUT);

  Serial.println("Setup finished!");
}

void loop()
{
	if(digitalRead(pirPin)==HIGH)
    Serial.println("Movement detected");
  else
    Serial.println("Nothing seen");
  
  delay(100);
  
}
