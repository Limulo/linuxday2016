#define LED_BT 13 // LED pin

//BT
boolean BT_led_state = LOW; // LED state


void setup() 
{
  //LED_BT setup
  pinMode(LED_BT, OUTPUT);
  digitalWrite(LED_BT, BT_led_state);

  
  //Serial communication setup
  Serial.begin(115200); // Serial monitoring
  delay(1000);
  Serial1.begin(115200); //Bluethooth monitoring
  delay(1000);
}

void loop() 
{
  digitalWrite(LED_BT, BT_led_state);
}

void serialEvent()
{
    // From serial monitor to bluetooth (Communication from Arduino to Processing)
    char c = Serial.read();
    Serial1.write(c);
    //Serial.print("\tcharacter "); Serial.print(c); Serial.println(" written!");
}

void serialEvent1()
{
  // Messages received from Processing over bluetooth
    char c = Serial1.read();
    //switch on/off according to action on Processing sketch
    if (c == '1')
      BT_led_state = HIGH;
    else if (c == '0')
      BT_led_state  =LOW;
    Serial.write(c);
}
