/*
 * LinuxDay Milano 2016
 * elettrodo rettangolare creato con foglio di rame da 6mm 
 * diviso in sezioni saldate fra loro. 
 * Il sensore è connesso all'elettrodo 0 della Touchboard con un cavo lungo
 * 1.7m connesso grazie a pinzette a coccodrillo.
 * L'elettrodo è incollato sotto una lastra di plastica spessa circa 5mm.
 * La riproduzione del file audio avviene alla rilevazione di un tocco.
 * Il file audio viene riprodotto nella sua durata intera ogni volta che un nuovo tocco
 * (un nuova persona interagisce) viene rilevato. 
 * Due interazione a distanza di tempo minore della durata del file audio 
 * fanno sì che il file audio sia messo in stop e quindi riavviato.
 */

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


#define REPLAY_MODE TRUE  // FALSE = toggle; TRUE = repeat

// 1st electrode only
#define ELECTRODE 0

unsigned int chimesDuration = 1000;
long chimesStatTime;

// sd card instantiation
SdFat sd;

boolean bChimesStatus = false;


// SETUP ////////////////////////////////////////////////////////////////////////////
void setup()
{  
  Serial.begin(57600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, bChimesStatus);
   
  //while (!Serial) ; {} //uncomment when using the serial monitor 

  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();

  if(!MPR121.begin(MPR121_ADDR)) 
    Serial.println("error setting up MPR121");
 
  MPR121.setInterruptPin(MPR121_INT);

  MPR121.setTouchThreshold(8);
  MPR121.setReleaseThreshold(4);  

  result = MP3player.begin();
  MP3player.setVolume(10,10);
 
  if(result != 0) 
  {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
  }

  chimesStatTime = - chimesDuration; // don't start playing chimes the first loop  
}

// LOOP /////////////////////////////////////////////////////////////////////////////
void loop()
{
  readTouchInputs();
  playChimes();
  digitalWrite( LED_BUILTIN, bChimesStatus );
}


void readTouchInputs()
{
  if(MPR121.touchStatusChanged())
  {
    MPR121.updateTouchData();
    if(MPR121.getNumTouches()<=1)
    { 
      if(MPR121.isNewTouch(ELECTRODE))
      {     
        //if(!MP3player.isPlaying())
        if( !bChimesStatus )
        {
          bChimesStatus = true;
          chimesStatTime = millis();
          //servo.write( 0 );
          MP3player.playTrack(ELECTRODE);
        }
        else
        {
        //   MP3player.stopTrack();
        //   MP3player.playTrack(ELECTRODE);
        }        
      }
      else
      {
        if(MPR121.isNewRelease(ELECTRODE))
        {
         // led_status = false;
         // digitalWrite(LED_BUILTIN, led_status);
        }
      }
    }
  }
}

void playChimes() 
{
  if( millis() - chimesStatTime < chimesDuration)
  {
    // play chimes 
  }
  else
  {
    bChimesStatus = false;
    //servo.write( 90 );
  }

}

