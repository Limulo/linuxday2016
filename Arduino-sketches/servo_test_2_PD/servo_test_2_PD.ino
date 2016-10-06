#include "Servo.h"

Servo servo;

void setup() 
{
  Serial.begin(9600);
  servo.attach(3, 1000, 2000);
}

void loop() 
{  
  delay(100);
}

void serialEvent()
{
  byte angle = Serial.read();
  angle =constrain( map(angle, 0, 127, 0, 180), 0, 180);
  servo.write(angle);
}

