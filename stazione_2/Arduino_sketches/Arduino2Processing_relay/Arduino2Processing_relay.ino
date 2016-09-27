#define LED 13 // LED pin
#define RELAY 8 // relay pin

char val; // data in
boolean led_state = LOW;    // LED state
boolean relay_state = LOW;  // relay state

void setup()
{
  pinMode(LED, OUTPUT);
  digitalWrite(LED, led_state);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, relay_state);
  

  Serial.begin(9600);
  while(!Serial);
}

void loop()
{
  if(Serial.available() > 0 ) 
  {   
    val = Serial.read();
    if (val == '1')
    {  
      led_state = true;
      relay_state = true;
    }
    else if (val == '0')
    {
      led_state = false;
      relay_state = false;
    }
    digitalWrite(LED, led_state);
    digitalWrite(RELAY, relay_state);
  }
  delay(1);
}
