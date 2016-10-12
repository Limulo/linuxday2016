#include "Servo.h"

Servo servo;
  int pos = 0;
  int angle = 90;
  int tangle = 25;

void setup() 
{
  Serial.begin(9600);
  servo.attach(9);//, 1000, 2000);
  servo.write(0);
}

void loop() 
{  
  while(pos < angle)
  {
    servo.write(pos);
    Serial.println(servo.read());
    delay(tangle);
    pos ++;
  }
  while(pos > 0)
  {
    servo.write(pos);
    Serial.println(servo.read());
    delay(tangle);
    pos--;
  }
}


