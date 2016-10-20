/* Relay ******************************************************************/
#include "Relay.h"
#define NUM_RELAYS 3
#define RELAY1 22
Relay relays[NUM_RELAYS];

#define LED 13

#define TIME 62
unsigned long t_actual, t_start;
unsigned long t_duration = 2; // minutes

/* Serial *****************************************************************/
boolean bSendSerial = false;

// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{  
  if( bSendSerial)
    Serial.begin( 9600 );
  
  /* relay ****************************************************************/
  int i;
  for(i=0; i<NUM_RELAYS; i++)
    relays[i].init( RELAY1+i, 2000 );

  t_start = millis();
  t_duration = t_duration * 60 * 1000;
  pinMode( LED, OUTPUT );
  digitalWrite( LED, LOW );
}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  t_actual = millis();
  if( bSendSerial)
    Serial.print(t_duration); Serial.print(", "); Serial.println(t_actual);
  if(t_actual - t_start < t_duration)
  {
    int i;
    for(i=0; i<NUM_RELAYS; i++)
      relays[i].turnOn();
    delay( TIME );
    for(i=0; i<NUM_RELAYS; i++)
      relays[i].turnOff();
    delay( TIME );
  }
  else
  {
    digitalWrite( LED, HIGH );
    delay( TIME );
    digitalWrite( LED, LOW );
    delay( TIME );
  }
}
