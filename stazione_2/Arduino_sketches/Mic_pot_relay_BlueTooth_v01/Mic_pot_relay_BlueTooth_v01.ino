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
  //Serial communication setup
  Serial.begin(9600); // Serial monitoring
  delay(1000);
  Serial1.begin(115200); //Bluethooth monitoring
  delay(1000);
  
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

void serialEvent1()
{
  char c = Serial1.read();
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

