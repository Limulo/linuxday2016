/* Mic ********************************************************************/
#include "Mic.h"
#define MIC A3
Mic mic;

// POT
#define POT A7
unsigned int threshold = 800;

/* Serial *****************************************************************/
boolean bSendSerial;

// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{

  /* Serial ***************************************************************/
  Serial.begin(9600, SERIAL_8N1); // Serial monitoring
  delay(1000);

  /* Mic ******************************************************************/
  mic.init( MIC, 50, threshold );

}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  //MIC stuff
  threshold = analogRead( POT );
  mic.getPeakToPeak( threshold );
  /*
  if( (mic.getPeakToPeak( threshold ) > threshold) )
  { 
    // Tunr ON the RELAY1 only if it is off
    relays[0].turnOn();
    Serial.println("\tMic ON;");
  }
  */
}

