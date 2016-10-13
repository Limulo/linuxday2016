/*
 * 13 Oct 2016
 * In this sketch we are aggregating some behaviour from previous sketches:
 * - proximity detection with a rectangular electrode;
 * - penguin shaking wing using a RC servo motor;
 * - MP3 file playing;
 * All these beahaviours are simultaneusly triggered when a proximity is 
 * detected.
 */

//servo
#include "Servo.h"
Servo servo;
float freq = 1; // Hz
byte phase = 180;  //degrees

// time variables
long t_elapsed_wave, t_initial_wave;
long t_duration_wave = 3000;

boolean bWaving = false;


// touch includes
#include <MPR121.h>
#include <Wire.h>
#define MPR121_ADDR 0x5C
#define MPR121_INT 4

// mp3 
#include <SPI.h>
#include <SdFat.h>
#include <SdFatUtil.h> 
#include <SFEMP3Shield.h>
SFEMP3Shield MP3player;
byte result;
SdFat sd; // sd card instantiation

#define REPLAY_MODE TRUE  // FALSE = toggle; TRUE = repeat

// 1st electrode only
#define ELECTRODE 0

// servo chymes
unsigned int t_duration_chimes = 1000; // tempo di rotazione del servo collegato ai chymes
long t_initial_chimes; // tempo iniziale per il compute dell'intervallo di funzionamento deu chymes
boolean bChimes = false; // servo ON/OFF


// SETUP ////////////////////////////////////////////////////////////////////////////
void setup()
{  
  Serial.begin(57600);
  //while (!Serial) ; {} //uncomment when using the serial monitor 

  /* SERVO **************************************************************************/
  // 750us e 2250us are min and max pulse width values for the Hitec HS-5055MG RC servo.
  // NOTE: Mp3 shield and MPR121 prevent PWM digital pins 3, 5, 9 from working properly.
  // The other PWM digital pins - 10. 11 and 13 - work as expected
  servo.attach(11, 750, 2250);
  servo.write(0);

  /* SD *****************************************************************************/
  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();

  /* MPR121 *************************************************************************/
  if(!MPR121.begin(MPR121_ADDR)) 
    //Serial.println("error setting up MPR121"); 
  MPR121.setInterruptPin(MPR121_INT);
  MPR121.setTouchThreshold(6);
  MPR121.setReleaseThreshold(4);  

  /* MP3 ****************************************************************************/
  result = MP3player.begin();
  MP3player.setVolume(1, 1);
  if(result != 0) 
  {
    //Serial.print("Error code: ");
    //Serial.print(result);
    //Serial.println(" when trying to start MP3 player");
  }

  /* CHIMES *************************************************************************/
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, bChimes);
  t_initial_chimes = - t_duration_chimes; // don't start playing chimes the first loop  
}


// LOOP /////////////////////////////////////////////////////////////////////////////
void loop()
{
  //Serial.println("loop");
  readTouchInputs();
  shakeChimes();
  shakeWing();
  digitalWrite( LED_BUILTIN, bChimes );
  delay(100);
}


// CUSTOM ///////////////////////////////////////////////////////////////////////////
void readTouchInputs()
{
  if( MPR121.touchStatusChanged() )
  {
    MPR121.updateTouchData();
     
    if(MPR121.isNewTouch(ELECTRODE))
    {     
      if( !bWaving )
      {
        bChimes = true;
        bWaving = true;
        t_initial_chimes = millis();
        t_initial_wave = millis();
        MP3player.playTrack(ELECTRODE);
        //Serial.print("bChimes:\t"); Serial.println(bChimes);
        //Serial.print("bWaving:\t"); Serial.println(bWaving);
      }    
    }
    else //non c'è un nuovo tocco
    {
      if(MPR121.isNewRelease(ELECTRODE)) 
      { 
        // do something 
      }
    }
  }
}

void shakeChimes() 
{
  if( millis() - t_initial_chimes < t_duration_chimes)
  {
    // shake chimes 
  }
  else
  {
    bChimes = false;
  }
}

void shakeWing()
{
  if( bWaving )
  {
    //Serial.println("moving");
    t_elapsed_wave = millis() - t_initial_wave;
    if(t_elapsed_wave < t_duration_wave)
    {
      // int wave = ((cos( (freq * (t_elapsed_wave/1000.0) * 2.0 * PI) + (phase * PI / 180.0)) + 1) / 2.0) * 180;
      int wave = ((cos( ((9*freq*t_elapsed_wave) + (25 * phase))/1432.4 )+1)*90);
      servo.write( wave );    
    }
    else 
    {
      //Serial.println("quit");
      servo.write(0);
      bWaving = false;
    }
  }
}

