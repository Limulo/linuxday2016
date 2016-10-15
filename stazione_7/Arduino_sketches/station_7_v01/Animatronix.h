//servo
#include "Servo.h"
#include "Arduino.h"

class Animatronix
{
  private:
    Servo servo;
    int pin;
    int pwmMin, pwmMax;
    boolean bState;
    int restPos;
    
    long t_initial, t_elapsed, t_duration; // time variables

    float freq; // Hz
    byte phase; //degrees

  public:

  Animatronix() {};
  void init( int _pin, int _pwmMin, int _pwmMax, int _restPos );
  void trigger();
  void update();
  boolean getState() { return bState; }
};

