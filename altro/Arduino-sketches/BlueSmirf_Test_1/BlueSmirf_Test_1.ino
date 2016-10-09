
void setup() 
{
  Serial.begin(115200); // Serial monitoring
  delay(1000);
  Serial1.begin(115200); //Bluethooth monitoring
  delay(1000);
}

void loop() 
{
  while(Serial.available())
  {
    char c = Serial.read();
    Serial1.write(c);
    //Serial.print("\tcharacter "); Serial.print(c); Serial.println(" written!");
  }
  
  while(Serial1.available())
  {
    char c = Serial1.read();
    Serial.write(c);
  }
}
