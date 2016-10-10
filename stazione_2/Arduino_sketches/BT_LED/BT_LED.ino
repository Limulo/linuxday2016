#define LED_BT 13 // LED pin
#define LED_MIC 7

//BT
char val; // bluetooth data in
boolean BT_led_state = LOW; // LED state

//MAX4466
// audio signal
unsigned int peakToPeak, signalMax, signalMin;  //mic signal management
unsigned int sample;                            //mic output

// time variables
unsigned long tStartMic;
unsigned long int tStartLed, tActualLed;
const int tWindowLed = 2000;
const int tWindowMic = 50;
boolean MIC_led_state = LOW; // LED state

void setup() 
{
  //LED_BT setup
  pinMode(LED_BT, OUTPUT);
  digitalWrite(LED_BT, BT_led_state);

  //LED_MIC setup
  pinMode(LED_MIC, OUTPUT);
  digitalWrite(LED_MIC, MIC_led_state);
  
  //Serial communication setup
  Serial.begin(115200); // Serial monitoring
  delay(1000);
  Serial1.begin(115200); //Bluethooth monitoring
  delay(1000);

  // windowing init
  tStartMic= millis();  // Start of sample window
  peakToPeak = 0;       // peak-to-peak level
  signalMax = 0;
  signalMin = 1024;

  tStartLed = tStartMic;
  tActualLed = tStartLed;
}

void loop() 
{
  digitalWrite(LED_BT, BT_led_state);

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

      if (!MIC_led_state)
     {
        MIC_led_state = true;
        digitalWrite(LED_MIC, MIC_led_state);
        tStartLed = millis();
   //     Serial.println("Led ON");
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
   if(((tActualLed-tStartLed)>=tWindowLed) && (MIC_led_state))
  {
    MIC_led_state = false;
    digitalWrite(LED_MIC, MIC_led_state);
 //   Serial.println("Led OFF");
  }
   delay(1);
}

void serialEvent()
{
    // From serial monitor to bluetooth (Communication from Arduino to Processing)
    val = Serial.read();
    Serial1.write(val);
    //Serial.print("\tcharacter "); Serial.print(c); Serial.println(" written!");
}

void serialEvent1()
{
  // Messages received from Processing over bluetooth
    val = Serial1.read();
    //switch on/off according to action on Processing sketch
    if (val == '1')
      BT_led_state = true;
    else if (val == '0')
      BT_led_state  =false;
    //Serial.write(c);
}
