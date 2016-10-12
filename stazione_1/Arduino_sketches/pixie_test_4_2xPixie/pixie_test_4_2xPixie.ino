/*
  Pixie reads data in at 115.2k serial, 8N1.
  Byte order is R1, G1, B1, R2, G2, B2, ... where the first triplet is the
  color of the LED that's closest to the controller. 1ms of silence triggers
  latch. 2 seconds silence (or overheating) triggers LED off (for safety).

  Do not look into Pixie with remaining eye!
*/

#include "SoftwareSerial.h"
#include "Adafruit_Pixie.h"

#define NUMPIXELS 2 // Number of Pixies in the strip
#define PIXIEPIN  2 // Pin number for SoftwareSerial output

SoftwareSerial pixieSerial(-1, PIXIEPIN);

Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &pixieSerial);
// Alternately, can use a hardware serial port for output, e.g.:
// Adafruit_Pixie strip = Adafruit_Pixie(NUMPIXELS, &Serial1);

long elapsedTime[NUMPIXELS];
long startTime[NUMPIXELS];
long T[NUMPIXELS];

uint8_t S[NUMPIXELS];
uint8_t D[NUMPIXELS];

uint8_t srcColor[NUMPIXELS][3]; // source color
uint8_t dstColor[NUMPIXELS][3]; // destination color
uint8_t finColor[NUMPIXELS][3]; // final color

boolean bRainbow = false;
boolean bLightSleep = false;

// brightness values are setted for all pixels
uint8_t brightness_master = 200;
uint8_t brightness_D = 50;
uint8_t brightness_S = 255;

byte lastAddr, val;
boolean bSendSerial = false;

// SETUP /////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  int i;

  Serial.begin(9600);
  //while(!Serial); // wait until Serial is ready to go
  
  //Serial.println("Ready to Pixie!");

  pixieSerial.begin(115200); // Pixie REQUIRES this baud rate
  // Serial1.begin(115200);  // <- Alt. if using hardware serial port

  strip.setBrightness( brightness_master );  // Adjust as necessary to avoid blinding

  //Serial.println("Red!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 255, 0, 0);
  strip.show();
  delay(300);

  //Serial.println("Green!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 0, 255, 0);
  strip.show();
  delay(300);

  //Serial.println("Blue!");
  for(i=0; i< NUMPIXELS; i++)
    strip.setPixelColor(i, 0, 0, 255);
  strip.show();
  delay(300);

  strip.clear();

  srcColor[0][0] = 255; // 1st Pixie - red 
  srcColor[0][1] = 0;   // 1st Pixie - green
  srcColor[0][2] = 0;   // 1st Pixie - blue

  srcColor[1][0] = 0;   // 2nd Pixie - red 
  srcColor[1][1] = 0;   // 2nd Pixie - green
  srcColor[1][2] = 255; // 2nd Pixie - blue

  // if in idle state, pixels are colored green
  for(i=0; i< NUMPIXELS; i++)
  {
    dstColor[i][0] = 0;
    dstColor[i][1] = 255;
    dstColor[i][2] = 0;
  }

  for(i=0; i< NUMPIXELS; i++)
  {
    T[i] = 2000;
    elapsedTime[i] = T;
  }
}

// LOOP //////////////////////////////////////////////////////////////////////////////////////////
void loop() 
{

  if( !bLightSleep ) 
  {
    int i;
    for(i=0; i< NUMPIXELS; i++)
    {
      if( elapsedTime[i] < T[i] )
      {
        elapsedTime[i] = millis() - startTime[i];
        if( elapsedTime[i] > T[i] )
          elapsedTime[i] = T[i];
  
        D[i] = (elapsedTime[i] * 255) / T[i];
        S[i] = 255 - D[i];
      }
      
      // red components
      finColor[i][0] = multiply( multiply( srcColor[i][0], S[i] ), brightness_S) + multiply( multiply( dstColor[i][0], D[i] ), brightness_D);
      // green components
      finColor[i][1] = multiply( multiply( srcColor[i][1], S[i] ), brightness_S) + multiply( multiply( dstColor[i][1], D[i] ), brightness_D);
      // blue components
      finColor[i][2] = multiply( multiply( srcColor[i][2], S[i] ), brightness_S) + multiply( multiply( dstColor[i][2], D[i] ), brightness_D);

      //Serial.print(componentS + componentD); Serial.println(";");
      //Serial.print("[");Serial.print(red_f); 
      //Serial.print(",\t");Serial.print(green_f); 
      //Serial.print(",\t");Serial.print(blue_f); 
      //Serial.println("];");
      
      strip.setPixelColor(i, finColor[i][0], finColor[i][1], finColor[i][2]);
    }
    strip.show();
  }
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
  
// SERIAL EVENT ////////////////////////////////////////////////////////////////////////
// 255, 1 - open 
// 255, 0 - close
void serialEvent()
{
  byte b = Serial.read();

  // record the address
  if( b >= 128 )
  {
    // the BYTE is an address
    lastAddr = b;
  }
  else 
  {
    val = b;
    switch( lastAddr ) 
    { 
      case 128:
        // luminosità master
        brightness_master = val<<1; // convert a 127 value to a 255 one
        strip.setBrightness( brightness_master );
        break;
        
      case 129:
        // luminosità Source
        brightness_S = val<<1;
        break;
        
      case 130:
        // luminosità Destination
        brightness_D = val<<1;
        break;

      case 140:
        // for this case we don't care the value 
        // received from serial communication.
        // bang 1st Pixel!
        bLightSleep = false;
        elapsedTime[0] = 0;
        startTime[0] = millis();
        break;

      case 141:
        // time 1st Pixel
        T[0] = (val << 5);
        break;
   
      case 150:
        // for this case we don't care the value 
        // received from serial communication.
        // bang 2nd Pixel!
        bLightSleep = false;
        elapsedTime[1] = 0;
        startTime[1] = millis();
        break;

      case 151:
        // time 2nd Pixel
        T[1] = (val << 5);
        break;

      case 240:
        // for this case we don't care the value 
        // received from serial communication.
        bLightSleep = true;
        strip.clear();
        break;

      case 255:
        if( val == 1)
          bSendSerial = true;
        else
          bSendSerial = false;
        break;
        
      default:
        // do nothing
        break;
    }
  }
}

