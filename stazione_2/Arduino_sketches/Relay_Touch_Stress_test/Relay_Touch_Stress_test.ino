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
#define NUM_RELAYS 1
#define RELAY1 22
Relay relays[NUM_RELAYS];

/* Serial *****************************************************************/
boolean bSendSerial = true;

#define LED 13

#define TIME 250
unsigned long t_actual_long, t_start_long;
unsigned long t_duration_long = 2; // minutes

unsigned long t_start_short;
unsigned long t_duration_short = TIME/2;

boolean bStatus, bPrevStatus;


// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{

  /* Serial ***************************************************************/
  if( bSendSerial)
    Serial.begin(9600, SERIAL_8N1); // Serial monitoring

  /* Touch ****************************************************************/
  TOUCH_init();
  
  /* relay ****************************************************************/
  int i;
  for(i=0; i<NUM_RELAYS; i++)
    relays[i].init( RELAY1+i, 2000 );

  pinMode( LED, OUTPUT );
  digitalWrite( LED, LOW );

  t_start_long = millis();
  t_duration_long = t_duration_long * 60 * 1000;
  t_start_short = millis();

  bStatus, bPrevStatus = false;

}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  
  TOUCH_update( false, 0 );
  delay (10 );
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
void TOUCH_update( boolean b, int _relay )
{
  currtouched = cap.touched();
  
  for (uint8_t i=0; i<N_ELECTRODE; i++) {
    // it if *is* touched and *wasnt* touched before, alert!
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" touched");
      bTouched[i] = true;
      if( b )
      {
        //Serial1.write(128 + 2 + i*3);
        //Serial1.write( bTouched[i] );
      }
      //if( i == N_ELECTRODE-1 )
      if( i == 0 )
      {
        //digitalWrite( relays[2], bTouched[i]);
        relays[ 0 ].turnOn();
      }
    }
    
    // if it *was* touched and now *isnt*, alert!
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      //Serial.print(i); Serial.println(" released");
      bTouched[i] = false;
      if( b )
      {
        //Serial1.write(128 + 2 + i*3);
        //Serial1.write( bTouched[i] );
      }
      //if( i == N_ELECTRODE-1 )
      if( i == 0 )
      {
        //digitalWrite( relays[2], bTouched[i]);
        relays[ 0 ].turnOff();
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




