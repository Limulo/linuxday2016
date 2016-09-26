/*
*
*  ADAFRUIT MAX4466 + LED
* ----------------------
* noise controlled LED switching
*
*/

// audio signal
unsigned int peakToPeak, signalMax, signalMin;  //mic signal management
unsigned int sample;                            //mic output

// time variables
unsigned long tStartMic;
unsigned long int tStartLed, tActualLed;
const int tWindowLed = 2000;
const int tWindowMic = 50;

// LED variables
#define LED 7
boolean led_status;


void setup() 
{
  Serial.begin(9600);
  
  led_status = false;
  pinMode(LED, OUTPUT);
  digitalWrite(LED, led_status);

  tStartMic= millis();  // Start of sample window
  peakToPeak = 0;       // peak-to-peak level
  signalMax = 0;
  signalMin = 1024;

  tStartLed = tStartMic;
  tActualLed = tStartLed;
}


void loop() 
{
// Are we inside the sample window?
// if so, then set min and max ...
   if(millis() - tStartMic < tWindowMic)
   {
       sample = analogRead(0);
       if (sample < 1024)  
       {
        if (sample > signalMax)
          signalMax = sample;  
        else if (sample < signalMin)
          signalMin = sample;  
       }
   }

// ... otherwise, calculate p2p value and, if it's the case, switch the LED on
   else
   {
    peakToPeak = signalMax - signalMin; 
    Serial.println(peakToPeak);
    
    if((peakToPeak > 500))
    { 

      if (!led_status)
     {
        led_status = true;
        digitalWrite(LED, led_status);
        tStartLed = millis();
        Serial.println("Led ON");
     }
    }
// then reset the timing and min/max values, so the next loop we can check it all again   
     tStartMic= millis();  // Start of sample window
     peakToPeak = 0;   // peak-to-peak level
     signalMax = 0;
     signalMin = 1024;


   }


//LED switch off logic  
 
   tActualLed = millis();

//Is the LED on? If so, for how long it's been working? Has the predefined LED working time already passed?
//If so, then give the LED some rest!
   if(((tActualLed-tStartLed)>=tWindowLed) && (led_status))
  {
    led_status = false;
    digitalWrite(LED, led_status);
    Serial.println("Led OFF");
  }
   delay(1);
   
 }
