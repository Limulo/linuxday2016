char val; // data in
int LED = 13; // LED pin
boolean led_state = LOW; // LED state

void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, led_state);

  Serial.begin(9600);
  while(!Serial);
}

void loop()
{
  if(Serial.available() > 0 ) 
  {   
    val = Serial.read();
    if (val == '1')  
      led_state = true;
    else if (val == '0')
      led_state = false;
    digitalWrite(LED, led_state);
  }
  delay(1);
}
