#include "Arduino.h"

class Mic
{
  private: 
    int pin;
    unsigned int peakToPeak, signalMax, signalMin;  //mic signal management
    unsigned int sample;   //mic output
    // time variables
    unsigned long t_start_mic;
    unsigned int t_window_mic;
 
  public:

  Mic() {};
  void init(int _pin, unsigned int _window);
  void trigger();
  int getPeakToPeak();
};

