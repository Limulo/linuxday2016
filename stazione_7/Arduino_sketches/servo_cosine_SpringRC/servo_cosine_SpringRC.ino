/*
 * A cosine to control servo rotation
 * Servo SpringRC SM-S4303R
 */
#include "Servo.h"

Servo servo;
boolean bSendSerial;

float freq = 1;  // Hz
byte phase = 90; //degrees

// time variables
long t_elapsed_servo, t_initial_servo;
long t_duration_servo = 3000;
boolean bShake = false;

// SETUP ///////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  while( !Serial );
  
  servo.attach(11, 1000, 2000);
  servo.write(90); // initial velocity = 0!
}

// LOOP ////////////////////////////////////////////////
void loop() 
{
  
  if( bShake )
  {
    t_elapsed_servo = millis() - t_initial_servo;
    if(t_elapsed_servo < t_duration_servo)
    {
      int wave = ((cos( (freq * (t_elapsed_servo/1000.0) * 2.0 * PI) + (phase * PI / 180.0)) + 1) / 2.0) * 180;
      //int wave = ((cos( ((9*freq*t_elapsed_servo) + (25 * phase))/1432.4 )+1)*90);
      servo.write( wave );    
    }
    else 
    {
      servo.write(90);
      bShake = false;
    }
  }

  /* do other things */

  
  while(Serial.available())
  {
    byte b = Serial.read();
    
    // is time to wave?
    if( b == 'w' )
    {
      t_initial_servo = millis();
      bShake = true;
    }
  }

  /*
  if(bSendSerial)
  {
    char feedback = servo.read();
    Serial.write( feedback );
  }
  */

  delay(5);
}

