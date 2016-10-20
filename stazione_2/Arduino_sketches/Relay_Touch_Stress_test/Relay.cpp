#include "Relay.h"

void Relay::init( int _pin, int _duration )
{
  pin = _pin;
  t_duration_relay = _duration;
  bStatus = false;
  pinMode( pin , OUTPUT);
  t_start_relay = millis();
  digitalWrite( pin , bStatus );
  
}

void Relay::update()
{
  // RELAY switch off logic  
  // Is the RELAY on? If so, for how long it's been working? 
  // Has the predefined working time of the RELAY already passed?
  // If so, then turn it OFF!
  if( bStatus && ((millis()-t_start_relay) > t_duration_relay) )
  {
    bStatus = false;
    digitalWrite( pin, bStatus);
    //Serial.print("\tRelay: "); Serial.println( bStatus ); 
  }
}


void Relay::turnOn()
{       
  bStatus = true;
  t_start_relay = millis();
  digitalWrite( pin , bStatus );
  //Serial.print("\tRelay: "); Serial.println( bStatus ); 
  delay( 5 );  
}

void Relay::turnOff()
{       
  bStatus = false;
  //t_start_relay = millis();
  digitalWrite( pin , bStatus );
  //Serial.print("\tRelay: "); Serial.println( bStatus );  
  delay( 5 ); 
}



  

