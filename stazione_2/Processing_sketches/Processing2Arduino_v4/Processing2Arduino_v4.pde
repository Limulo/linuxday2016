/*
This sketch renders a button on the screen.
When you click it, the sketch will send messages
to Arduino via Bluetooth serial communication.
*/

import processing.serial.*;

Serial bluetooth;

Button button;

color base = color(200, 200, 0);
color pressed = color(120, 0, 120);


// SETUP ///////////////////////////////////////////////////////////////////////////
void setup()
{
  size(640, 480);
  background(120);
  
  //println(Serial.list());
  bluetooth = new Serial(this, "/dev/tty.blue_limulo-RNI-SPP", 115200);
  
  button = new Button(200, 200, 100);
  
}

// DRAW ////////////////////////////////////////////////////////////////////////////
void draw()
{   
  button.display();
}


// OTHER ///////////////////////////////////////////////////////////////////////////
void mousePressed()
{
  if( button.update(mouseX, mouseY) )
    bluetooth.write('1');
  else
    bluetooth.write('0');
}