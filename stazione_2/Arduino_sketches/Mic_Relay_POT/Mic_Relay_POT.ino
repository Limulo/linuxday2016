#include "Mic.h"

// audio signal
#define MIC A12

// LED variables
#define LED 22
boolean bLedStatus;
unsigned long t_start_led;
const int t_duration_led = 2000;

// POT
#define POT A7
unsigned int threshold = 800;

Mic mic;


// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  mic.init( MIC, 50 );

  /* LED *******************************************************************/
  bLedStatus = false;
  pinMode(LED, OUTPUT);
  digitalWrite(LED, bLedStatus);
  t_start_led = millis();;
}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  threshold = analogRead( POT );
  if( (mic.getPeakToPeak() > threshold) && !bLedStatus)
  { 
    //Serial.println( threshold );
    // Light the LED only if it is off     
    bLedStatus = true;
    t_start_led = millis();
    digitalWrite(LED, bLedStatus);
    Serial.println("\tLed ON");
  }
  
  // LED switch off logic  
  // Is the LED on? If so, for how long it's been working? Has the predefined LED working time already passed?
  // If so, then give the LED some rest!
  if( bLedStatus && ((millis()-t_start_led) > t_duration_led) )
  {
    bLedStatus = false;
    digitalWrite(LED, bLedStatus);
    //Serial.println("Led OFF");
  }
}
