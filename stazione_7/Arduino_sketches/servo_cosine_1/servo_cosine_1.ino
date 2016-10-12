/*
 * A cosine to control servo rotation
 * Servo Hitec HS-5055MG  
 */
#include "Servo.h"
//#define PI 3.14159

Servo servo;
boolean bSendSerial;

float freq = 1; // Hz
byte phase = 180;  //degrees

// time variables
long elapsedTime, initialTime;
long waveTime = 3000;
boolean bWaving = false;

// SETUP ///////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);

  // 750us e 2250us are min and max pulse width values 
  // for the Hitec HS-5055MG RC servo
  servo.attach(9, 750, 2250);
  servo.write(0);
  
  bSendSerial = false;
}

// LOOP ////////////////////////////////////////////////
void loop() 
{
  
  if( bWaving )
  {
    elapsedTime = millis() - initialTime;
    if(elapsedTime < waveTime)
    {
      // int wave = ((cos( (freq * (elapsedTime/1000.0) * 2.0 * PI) + (phase * PI / 180.0)) + 1) / 2.0) * 180;
      int wave = ((cos( ((9*freq*elapsedTime) + (25 * phase))/1432.4 )+1)*90);
      servo.write( wave );    
    }
    else 
    {
      servo.write(0);
      bWaving = false;
    }
  }

  /* do other things */

  
  while(Serial.available())
  {
    byte b = Serial.read();
    
    // is time to wave?
    if( b == 'w' )
    {
      initialTime = millis();
      bWaving = true;
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

