#include "Animatronix.h"

void Animatronix::init( int _pin, int _pwmMin, int _pwmMax, int _restPos )
{
  restPos = _restPos;
  
  servo.attach(_pin, _pwmMin, _pwmMax);
  servo.write( restPos );

  freq = 1;
  phase = 180; 
  t_duration = 3000; 

  bState = false;
}


void Animatronix::update() 
{
  if( bState )
  {
    t_elapsed = millis() - t_initial;
    if(t_elapsed < t_duration)
    {
      // int wave = ((cos( (freq * (t_elapsed/1000.0) * 2.0 * PI) + (phase * PI / 180.0)) + 1) / 2.0) * 180;
      int wave = ((cos( ((9*freq*t_elapsed) + (25 * phase))/1432.4 )+1)*90);
      servo.write( wave );    
    }
    else 
    {
      servo.write( restPos );
      bState = false;
    }
  }
}

void Animatronix::trigger()
{
  bState = true;
  t_initial = millis();
}

