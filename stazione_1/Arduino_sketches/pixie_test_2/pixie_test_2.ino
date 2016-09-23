/*
  Pixie reads data in at 115.2k serial, 8N1.
  Byte order is R1, G1, B1, R2, G2, B2, ... where the first triplet is the
  color of the LED that's closest to the controller. 1ms of silence triggers
  latch. 2 seconds silence (or overheating) triggers LED off (for safety).

  Do not look into Pixie with remaining eye!
*/

#include "SoftwareSerial.h"
#include "Adafruit_Pixie.h"

#define NUMPIXELS 1 // Number of Pixies in the strip
#define PIXIEPIN  6 // Pin number for SoftwareSerial output

SoftwareSerial pixieSerial(-1, PIXIEPIN);

Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &pixieSerial);
// Alternately, can use a hardware serial port for output, e.g.:
// Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &Serial1);


long elapsedTime, startTime, T = 2000;
uint8_t S, D;
uint8_t red_s, green_s, blue_s; // source color
uint8_t red_d, green_d, blue_d; // destination color
uint8_t red_f, green_f, blue_f; // final color

boolean bRainbow = false;

uint8_t brightness_master = 200;
uint8_t brightness_D = 50;
uint8_t brightness_S = 255;

// SETUP /////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  int i;

  Serial.begin(9600);
  while(!Serial); // wait until Serial is ready to go
  
  Serial.println("Ready to Pixie!");

  pixieSerial.begin(115200); // Pixie REQUIRES this baud rate
  // Serial1.begin(115200);  // <- Alt. if using hardware serial port

  strip.setBrightness( brightness_master );  // Adjust as necessary to avoid blinding

  Serial.println("Red!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 255, 0, 0);
  strip.show();
  delay(300);

  Serial.println("Green!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 0, 255, 0);
  strip.show();
  delay(300);

  Serial.println("Blue!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 0, 0, 255);
  strip.show();
  delay(300);
  
  red_s = 255;
  green_s = 0;
  blue_s = 0;

  red_d = 0;
  green_d = 255;
  blue_d = 0;

  elapsedTime = T;
}

// LOOP //////////////////////////////////////////////////////////////////////////////////////////
void loop() {

  if( elapsedTime < T )
  {
    elapsedTime = millis() - startTime;
    if( elapsedTime > T )
      elapsedTime = T;
    
    D = (elapsedTime * 255) / T;
    S = 255 - D;

    // red components
    red_f = multiply( multiply( red_s, S ), brightness_S) + multiply( multiply( red_d, D ), brightness_D);

    // green components
    green_f = multiply( multiply( green_s, S ), brightness_S) + multiply( multiply( green_d, D ), brightness_D);

    // blue components
    blue_f = multiply( multiply( blue_s, S ), brightness_S) + multiply( multiply( blue_d, D ), brightness_D);
    
    //Serial.print(componentS + componentD); Serial.println(";");
    Serial.print("[");Serial.print(red_f); 
    Serial.print(",\t");Serial.print(green_f); 
    Serial.print(",\t");Serial.print(blue_f); 
    Serial.println("];");
  }

  int i;
  for(i=0; i<NUMPIXELS; i++)
  {
    strip.setPixelColor(i, red_f, green_f, blue_f);
  }
  strip.show();
  delay(10);
  
  /*
  if( bRainbow ) 
  {
    Serial.println("Rainbow!");
    rainbowCycle(10);
  }
  */
  
}

// CUSTOM ////////////////////////////////////////////////////////////////////////////////////////

uint8_t multiply( uint8_t _cmp, uint8_t _factor)
{   
    uint8_t cmp = 0;
    uint8_t factor = _factor + 1;
    if(!factor)
       cmp = _cmp;  
    else
    {
        uint16_t c16 = (uint16_t)_cmp;
        uint16_t f16 = (uint16_t)factor;
        cmp = (c16*f16)>>8;
    } 
    return cmp;
}


// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< NUMPIXELS; i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
// 255 / 3 = 85
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void serialEvent()
{
  char b = Serial.read();
  if( b == 'a')
  {
    strip.clear();
    bRainbow = false;
    Serial.println("Stop rainbow");
  } 
  else if( b == 'x' )
  {
    bRainbow = true;
  }
  else if( b == 's' )
  {
    elapsedTime = 0;
    startTime = millis();
    D = (elapsedTime * 255) / T;
    S = 255 - D;

    // red components
    red_f = multiply( multiply( red_s, S ), brightness_S) + multiply( multiply( red_d, D ), brightness_D);

    // green components
    green_f = multiply( multiply( green_s, S ), brightness_S) + multiply( multiply( green_d, D ), brightness_D);

    // blue components
    blue_f = multiply( multiply( blue_s, S ), brightness_S) + multiply( multiply( blue_d, D ), brightness_D);
    
    //Serial.print(componentS + componentD); Serial.println(";");
    Serial.print("[");Serial.print(red_f); 
    Serial.print(",\t");Serial.print(green_f); 
    Serial.print(",\t");Serial.print(blue_f); 
    Serial.println("];");    
  }
}

