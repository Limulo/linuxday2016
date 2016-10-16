#include "Mic.h"
#include "Relay.h"

// audio signal
#define MIC A12
Mic mic;

// POT
#define POT A7
unsigned int threshold = 800;

// RELAY variables
#define NUM_RELAYS 3
#define RELAY1 22
Relay relays[3];


// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  
  mic.init( MIC, 50 );
  
  // relay initialization *************************************************/
  int i;
  for(i=0; i<NUM_RELAYS; i++)
    relays[i].init( RELAY1+i, 2000 );
}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  threshold = analogRead( POT );
  
  relays[0].update();
  //relays[1].update();
  //relays[2].update();
  
  if( (mic.getPeakToPeak() > threshold) && !relays[0].getStatus() )
  { 
    //Serial.println( threshold );
    // Tunr ON the RELAY1 only if it is off
    relays[0].turnOn();
  }
}

void serialEvent()
{
  char c = Serial.read();
  switch (c)
  {
    case '1':
      relays[1].turnOn();
      break;
    case '0':
      relays[1].turnOff();
      break;
    default:
      break;   
  }
}

