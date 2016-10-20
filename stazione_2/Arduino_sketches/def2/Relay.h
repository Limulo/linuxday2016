#include "Arduino.h"

class Relay
{
  private:
    int pin;
    boolean bStatus;
    unsigned long t_start_relay;
    unsigned int t_duration_relay;

  public:

  Relay() {}
  void init(int pin, int duration);
  boolean getStatus() { return bStatus; }
  void turnOn();
  void turnOff();
  void update();  
};

