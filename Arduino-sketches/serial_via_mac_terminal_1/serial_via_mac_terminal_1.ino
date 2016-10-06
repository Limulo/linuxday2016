
void setup() 
{
  Serial.begin(9600); // Serial monitoring
}

void loop() 
{
  delay(10);
}

void serialEvent() 
{
  char c = Serial.read();
  Serial.print("character ");
  Serial.print(c);
  Serial.println(" received!");
}

