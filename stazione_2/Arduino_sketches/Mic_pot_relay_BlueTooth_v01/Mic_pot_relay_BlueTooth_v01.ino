/* 
 *  Use this sketch with this Processing Code

import processing.serial.*;

Serial bluetooth;
boolean lit = false;

color base = color(200, 200, 0);
color pressed = color(120, 0, 120);

void setup()
{
  size(640, 480);
  background(120);
  
  //println(Serial.list());
  bluetooth = new Serial(this, "/dev/tty.blue_limulo-RNI-SPP", 115200);
  
}

void draw()
{   
  noStroke();
  if(lit)
    fill(pressed);
  else
    fill(base);
  rect(50, 50, 80, 80);
}

void mousePressed()
{
  if((isInRange(mouseX, 50, 130)) && (isInRange(mouseY, 50, 130)))
  {
    if(lit)
    {
      lit = false;
      bluetooth.write('0');
    }
    else
    {
      lit = true;
      bluetooth.write('1');
    }
  }
}

boolean isInRange(int val, int dim1, int dim2)
{
  if(val >= dim1 && val <= dim2)
    return true;
  else
    return false;
}
*/

#include "Mic.h"
#include "Relay.h"

// audio signal
#define MIC A12
Mic mic;

// POT
#define POT A7
unsigned int threshold = 800;

// RELAY variables
#define NUM_RELAYS 3
#define RELAY1 22
Relay relays[3];


// SETUP ///////////////////////////////////////////////////////////////////
void setup() 
{
  //Serial communication setup
  Serial.begin(9600); // Serial monitoring
  delay(1000);
  Serial1.begin(115200); //Bluethooth monitoring
  delay(1000);
  
  mic.init( MIC, 50 );
  
  // relay initialization *************************************************/
  int i;
  for(i=0; i<NUM_RELAYS; i++)
    relays[i].init( RELAY1+i, 2000 );
}


// LOOP ////////////////////////////////////////////////////////////////////
void loop() 
{
  threshold = analogRead( POT );
  
  relays[0].update();
  //relays[1].update();
  //relays[2].update();
  
  if( (mic.getPeakToPeak() > threshold) && !relays[0].getStatus() )
  { 
    //Serial.println( threshold );
    // Tunr ON the RELAY1 only if it is off
    relays[0].turnOn();
  }
}

void serialEvent1()
{
  char c = Serial1.read();
  switch (c)
  {
    case '1':
      relays[1].turnOn();
      break;
    case '0':
      relays[1].turnOff();
      break;
    default:
      break;   
  }
}

