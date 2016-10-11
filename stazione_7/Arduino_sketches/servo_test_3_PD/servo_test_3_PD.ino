/*
 * Test - Servo HS-5055MG Hitec pilotato da PureData
 */
#include "Servo.h"

Servo servo;
boolean bSendSerial;


// SETUP ///////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  //servo.attach(9);

  // 750us e 2250us are min and max pulse width values 
  // for the Hitec HS-5055MG RC servo
  servo.attach(9, 750, 2250); 
  bSendSerial = false;
}

// LOOP ////////////////////////////////////////////////
void loop() 
{  
  while(Serial.available())
  {
    byte angle = Serial.read();
    if( angle == 255 )
      bSendSerial = true;
    else if( angle == 254 )
      bSendSerial = false;
    else
    {
      //angle = constrain( angle, 21, 166);
      servo.write(angle);
    }
  }
  
  if(bSendSerial)
  {
    char feedback = servo.read();
    Serial.write( feedback );
  }

  delay(5);
}

