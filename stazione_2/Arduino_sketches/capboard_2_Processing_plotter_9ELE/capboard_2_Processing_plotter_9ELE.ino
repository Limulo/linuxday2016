/*
* 18-Oct-2016
*/

#include <Wire.h>
#include "Limulo_MPR121.h"

/* MPR121 - TouchBox */
Limulo_MPR121 cap = Limulo_MPR121();

// Keeps track of the last pins touched so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
boolean bTouched[9];


// ---------------------------------------------- //
boolean bSendSerial = false;

// SETUP ///////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin( 115200, SERIAL_8N1 );
  
  // TOUCHBOX
  TOUCH_init();

  int i;
  for(i=0; i<9; i++)
    bTouched[i] = false;

}

// LOOP ////////////////////////////////////////////////////////////////////////////////
void loop() 
{  
  TOUCH_read( bSendSerial );
    
  //delay( 50 ); // put a delay so it isn't overwhelming  
}


// TOUCH BOX ///////////////////////////////////////////////////////////////////////////
void TOUCH_init() 
{
  // TOUCHBOX
  if (!cap.begin(0x5A)) 
  {
    //Serial.println( "MPR121 not found, check wiring?" );
    while(1);
  }
  //Serial.println( "MPR121 found!" ); 
}

void TOUCH_read( boolean b )
{
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<12; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" touched");
      bTouched[i] = true;
    }
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" released");
      bTouched[i] = false;
    }
  }

  // reset our state
  lasttouched = currtouched;

  // Send Serial data ////////////////////////////////////////////////////////////  
  if( b )
  {
    int i;
    for( i=0; i<9; i++) 
    {
      int filt = cap.filteredData( i );
      int base = cap.baselineData( i );
      
      // first electrode
      Serial.write(128 + i*3);
      Serial.write(base / 8);
      
      Serial.write(128 + 1 + i*3);
      Serial.write(filt / 8);
      
      Serial.write(128 + 2 + i*3);
      Serial.write( bTouched[i] );
    }
  }
}


// SERIAL EVENT /////////////////////////////////////////////////////////////////////
void serialEvent()
{
  byte b = Serial.read();
  if (b == 'o')
    bSendSerial = true;
  else if (b == 'c')
    bSendSerial = false;
  else if (b == 'r')
    cap.reset();
}
