#include "Servo.h"

Servo servo;
  int pos = 0;
  int angle = 90;
  int tangle = 5;

void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  servo.attach( 11, 1000, 2000 );
  servo.write(90);
}

void loop() 
{  
  while(Serial.available()>0)
  {
    char c = Serial.read();
    switch( c )
    {
      case '1':
        servo.write(0);
        delay( 100 );
        break;
       
      case '2':
        servo.write( 90 );
        delay( 100 );
        break;

      case '3': 
        servo.write( 180 );
        delay( 100 );
        break;
        
      default:
        // do nothing
        break;
    }
  }

  delay( 10 );
  
}
