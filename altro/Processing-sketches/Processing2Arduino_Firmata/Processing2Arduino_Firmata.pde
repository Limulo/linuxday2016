/*
*  TODO:
*  1) caricare lo sketch "Firmata Standard" su Arduino
*  2) cambiare nome alla libreria Firmata da "Arduino.jar" a "arduino.jar"
*  pin 3 (out): LED
*  pin 2 (in) : push button
*/

import processing.serial.*;
import cc.arduino.*;

Arduino arduino;

final int led_pin = 3;
final int but_pin = 2;

boolean lit = false;
boolean pressed = false;

color led_base = color(200, 200, 0);
color led_pressed = color(120, 0, 120);

void setup() 
{
  size(470, 280);
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(led_pin, Arduino.OUTPUT);
  arduino.pinMode(but_pin, Arduino.INPUT);
}

void draw() 
{
  background(led_base);
  stroke(led_pressed);
  
  if (lit)
      fill(led_pressed);
  else
    fill(led_base);
  rect(50, 50, 80, 80);
  
  if (arduino.digitalRead(but_pin) == Arduino.LOW)
    fill (led_pressed);
  else
    fill (led_base);
  
  ellipse(200, 90, 50, 50);
  
}

void mousePressed()
{

  if((isInRange(mouseX, 50, 130)) && (isInRange(mouseY, 50, 130)))
  {
    if(lit)
    {
      lit = false;
      arduino.digitalWrite(led_pin, Arduino.LOW);
    }
    else
    {
      lit = true;
      arduino.digitalWrite(led_pin, Arduino.HIGH);
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