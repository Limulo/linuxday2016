/*
*
*  ADAFRUIT MAX4466 + LED
* ----------------------
* noise controlled LED switching
*
*/

// audio signal
#define MIC A0
unsigned int peakToPeak, signalMax, signalMin;  //mic signal management
unsigned int sample;                            //mic output
// time variables
unsigned long t_start_mic;
const int t_window_mic = 50;
unsigned int threshold = 250;

// LED variables
#define LED 13
boolean bLedStatus;
unsigned long t_start_led, t_actual_led;
const int t_duration_led = 2000;


// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  
  bLedStatus = false;
  pinMode(LED, OUTPUT);
  digitalWrite(LED, bLedStatus);

  /* MIC *******************************************************************/
  signalMax = 0;
  signalMin = 1024;
  t_start_mic = millis(); // Start of sample window
  peakToPeak = 0;         // peak-to-peak level

  /* LED *******************************************************************/
  t_start_led = t_start_mic;
  t_actual_led = t_start_led;
}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  // Are we inside the sample window? if so, then set min and max ...
  if(millis() - t_start_mic < t_window_mic)
  {
    sample = analogRead( MIC );
    //Serial.print("\t"); Serial.println( sample );
    if (sample < 1024)  
    {
      if (sample > signalMax)
        signalMax = sample;  
      if (sample < signalMin)
        signalMin = sample;  
    }
  }
  // ... otherwise, calculate peak to peack value and, 
  // if it's the case, switch the LED on
  else
  {
    peakToPeak = signalMax - signalMin; 
    
    //Serial.print(signalMax); Serial.print(" - ");
    //Serial.print(signalMin); Serial.print(" = ");
    //Serial.print(peakToPeak); Serial.println(";");

    if( !bLedStatus && (peakToPeak > threshold) )
    { 
      // Light the LED only if it is off     
      bLedStatus = true;
      t_start_led = millis();
      digitalWrite(LED, bLedStatus);
      //Serial.println("Led ON");
    }
    
    // then reset the timing and min/max values, so the next loop we can check it all again   
    t_start_mic = millis();  // Start of sample window
    peakToPeak = 0; // peak-to-peak level
    signalMax = 0;
    signalMin = 1024;
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
