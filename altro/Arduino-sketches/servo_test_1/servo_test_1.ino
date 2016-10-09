#include "Servo.h"

Servo servo;
int angle;

void setup() 
{
  Serial.begin(9600);
  servo.attach(3, 1000, 2000);
  servo.write(90);
}

void loop() 
{  
  delay(100);
}

void serialEvent()
{
  byte b = Serial.read();
  angle = servo.read();
  Serial.print("Before interaction: "); Serial.println(angle);
  if(b == 'a')
    servo.write(0);
  else if(b == 'l')
    servo.write(180);
  else
    servo.write(90);
  angle = servo.read();
  Serial.print("After interaction: "); Serial.println(angle);
  Serial.println();
  

    
}

