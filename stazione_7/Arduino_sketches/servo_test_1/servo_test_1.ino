#include "Servo.h"

Servo servo;
  int pos = 0;
  int angle = 90;
  int tangle = 5;

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
    delay(tangle);
    pos ++;
  }
  while(pos > 0)
  {
    servo.write(pos);
    delay(tangle);
    pos--;
  }
}

/*void serialEvent()
{
  byte b = Serial.read();
 // angle = servo.read();
 // Serial.print("Before interaction: "); Serial.println(angle);
  if(b == 'a')
    servo.write(0);
  else if(b == 'l')
    servo.write(180);
  else
    servo.write(90);
 // angle = servo.read();
 // Serial.print("After interaction: "); Serial.println(angle);
  Serial.println();
  

    
}
*/
