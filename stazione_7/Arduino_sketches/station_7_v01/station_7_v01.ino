/*
 * 14 Oct 2016
 * In this sketch we are aggregating some behaviour from previous sketches:
 * - proximity detection with a rectangular electrode;
 * - penguin shaking wing using a RC servo motor ( Hitec HS-5055MG RC servo );
 * - chimes shaking using a 360 servo motor ( SpringRc SM-S4303R 360° servo );
 * - MP3 file playing;
 * All these beahaviours are simultaneusly triggered when a proximity is 
 * detected.
 */

#include "Animatronix.h"
Animatronix penguin; // Hitec HS-5055MG RC servo
Animatronix chimes;  // SpringRc SM-S4303R 360° servo

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

// SETUP ////////////////////////////////////////////////////////////////////////////
void setup()
{  
  Serial.begin(57600);
  //while (!Serial) ; {} //uncomment when using the serial monitor 

  /* ANIMATRONIX ********************************************************************/
  penguin.init(10, 750, 2250, 0);
  chimes.init(11, 1000, 2000, 90);

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
}


// LOOP /////////////////////////////////////////////////////////////////////////////
void loop()
{
  readTouchInputs();
  
  chimes.update();
  penguin.update();
  
  delay(10);
}


// CUSTOM ///////////////////////////////////////////////////////////////////////////
void readTouchInputs()
{
  if( MPR121.touchStatusChanged() )
  {
    MPR121.updateTouchData();
     
    if(MPR121.isNewTouch(ELECTRODE))
    {     
      if( !penguin.getState() )
      {
        penguin.trigger();
        chimes.trigger();

        MP3player.playTrack(ELECTRODE);
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
