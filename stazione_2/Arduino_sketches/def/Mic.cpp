#include "Mic.h"

void Mic::init(int _pin,  unsigned int _window )
{
  pin = _pin;
  t_window_mic = _window;
  trigger();
}

void Mic::trigger()
{
  signalMax = 0;
  signalMin = 1024;
  t_start_mic = millis(); // Start of sample window
}


int Mic::getPeakToPeak() 
{
  peakToPeak = 0;

  // Are we inside the sample window? if so, then set min and max ...
  if(millis() - t_start_mic < t_window_mic)
  {
    sample = analogRead( pin );
    //Serial.print("\t"); Serial.println( sample );
    if (sample < 1024)  
    {
      if (sample > signalMax)
        signalMax = sample;  
      else if (sample < signalMin)
        signalMin = sample;  
    }
  }
  else
  {
    peakToPeak = signalMax - signalMin;
    //Serial.print(signalMax); Serial.print(" - ");
    //Serial.print(signalMin); Serial.print(" = ");
    //Serial.print(peakToPeak); Serial.println(" / ");
    //Serial.println( threshold );
    
    trigger();
  }
  return peakToPeak;
}

