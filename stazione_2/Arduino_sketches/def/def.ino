/* Mic ********************************************************************/
//#include "Mic.h"
//#define MIC A12
//Mic mic;

// POT
//#define POT A7
//unsigned int threshold = 800;

/* Touch ******************************************************************/
#include <Wire.h>
#include "Limulo_MPR121.h"

Limulo_MPR121 cap = Limulo_MPR121();
#define N_ELECTRODE 9
uint16_t lasttouched = 0;
uint16_t currtouched = 0;
boolean bTouched[ N_ELECTRODE ];

/* Relay ******************************************************************/
#include "Relay.h"
#define NUM_RELAYS 2
#define RELAY1 22
Relay relays[NUM_RELAYS];

/* Serial *****************************************************************/
boolean bSendSerial;


// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{

  /* Serial ***************************************************************/
  //Serial.begin(9600, SERIAL_8N1); // Serial monitoring
  //delay(1000);
  
  Serial1.begin(115200, SERIAL_8N1); //Bluethooth monitoring
  delay(1000);

  bSendSerial = false;

  /* Mic ******************************************************************/
  //mic.init( MIC, 50, threshold );

  /* Touch ****************************************************************/
  TOUCH_init();
  
  /* relay ****************************************************************/
  int i;
  for(i=0; i<NUM_RELAYS; i++)
    relays[i].init( RELAY1+i, 2000 );
}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  /* MIC stuff
  threshold = analogRead( POT );
  if( (mic.getPeakToPeak( threshold ) > threshold) && !relays[0].getStatus() )
  { 
    // Tunr ON the RELAY1 only if it is off
    relays[0].turnOn();
    Serial.println("\tMic ON;");
  }
  */

  /*
  relays[0].update();
  //relays[1].update();
  //relays[2].update();
  */
  
  TOUCH_read( bSendSerial );
}

// TOUCH BOX ///////////////////////////////////////////////////////////////////////////
void TOUCH_init() 
{
  // TOUCHBOX
  if (!cap.begin(0x5A)) 
  {
    Serial.println( "MPR121 not found, check wiring?" );
    while(1);
  }
  Serial.println( "MPR121 found!" ); 

  int i;
  for(i=0; i<9; i++)
    bTouched[i] = false;
}


/*
 * This function write on Serial only whe Arduino detects a NEW touch or release.
 * Normally each electrode would have sent 3 bytes (and their corresponding addresses) 
 * representing baseline, filtered and touched values.
 * In this case we are interested only in electrodes touch statuses so we send only 
 * a single couple of byte:
 * - addr + touch status
 * All electrode's values addresses are numbers from 128 to 255. In particular the 
 * Electrode Touch Value Address is created adding 128 to 2 (because normally the touch 
 * value is the third value we sens for each electrode) + i*3 .
 */
void TOUCH_read( boolean b )
{
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<N_ELECTRODE; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" touched");
      bTouched[i] = true;
      if( b )
      {
        Serial1.write(128 + 2 + i*3);
        Serial1.write( bTouched[i] );
      }
      if( i == N_ELECTRODE-1 )
      {
        //digitalWrite( relays[2], bTouched[i]);
        relays[1].turnOn();
      }
    }
    
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" released");
      bTouched[i] = false;
      if( b )
      {
        Serial1.write(128 + 2 + i*3);
        Serial1.write( bTouched[i] );
      }
      if( i == N_ELECTRODE-1 )
      {
        //digitalWrite( relays[2], bTouched[i]);
        relays[1].turnOff();
      }
    }    
  }

  // reset our state
  lasttouched = currtouched;
  
  /*
  // Send baseline/filtered/touched data ************************************************
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
  */
}


// SERIAL EVENT ////////////////////////////////////////////////////////////////////
/*
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
*/

// Bluetooth
void serialEvent1()
{
  char c = Serial1.read();
  switch (c)
  {
    case 'o':
      bSendSerial = true;
      break;
    case 'c':
      bSendSerial = false;
      break;
    case 'r':
      cap.reset();
      break;
    case '1':
      relays[0].turnOn();
      break;
    case '0':
      relays[0].turnOff();
      break;
    default:
      // do nothing
      break;   
  }
}

