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
SdFat sd; // sd card instantiation

#define REPLAY_MODE TRUE  // FALSE = toggle; TRUE = repeat

// 1st electrode only
#define ELECTRODE 0

// servo chymes
unsigned int chimesDuration = 1000; // tempo di rotazione del servo collegato ai chymes
long chimesStartTime; // tempo iniziale per il compute dell'intervallo di funzionamento deu chymes
boolean bChimesStatus = false; // servo ON/OFF


// SETUP ////////////////////////////////////////////////////////////////////////////
void setup()
{  
  Serial.begin(9600);
  while (!Serial) ; {} //uncomment when using the serial monitor 

  if(!sd.begin(SD_SEL, SPI_HALF_SPEED)) sd.initErrorHalt();

  if(!MPR121.begin(MPR121_ADDR)) 
    Serial.println("error setting up MPR121"); 
  MPR121.setInterruptPin(MPR121_INT);
  MPR121.setTouchThreshold(6);
  MPR121.setReleaseThreshold(4);  

  result = MP3player.begin();
  MP3player.setVolume(0, 0);
  if(result != 0) 
  {
    Serial.print("Error code: ");
    Serial.print(result);
    Serial.println(" when trying to start MP3 player");
  }
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, bChimesStatus);
  chimesStartTime = - chimesDuration; // don't start playing chimes the first loop  
}

// LOOP /////////////////////////////////////////////////////////////////////////////
void loop()
{
  readTouchInputs();
  playChimes();
  digitalWrite( LED_BUILTIN, bChimesStatus );
  delay(150);
}


void readTouchInputs()
{
  if(MPR121.touchStatusChanged())
  {
    MPR121.updateTouchData();
 //   if(MPR121.getNumTouches()<=1)
    { 
      if(MPR121.isNewTouch(ELECTRODE))
      {     
        //if(!MP3player.isPlaying())
        if( !bChimesStatus )
        {
          bChimesStatus = true;
          chimesStartTime = millis();
          //servo.write( 0 );
          MP3player.playTrack(ELECTRODE);
          //Serial.println(" nuovo tocco\tchimes falso");

        }
 /*       else // un nuovo tocco mentre stiamo ancora gestendo il precedente
        {
        //   MP3player.stopTrack();
        //   MP3player.playTrack(ELECTRODE);
          Serial.println(" nuovo tocco\tchimes vero");
        } 
 */       
      }
      else //non c'è un nuovo tocco
      {
        if(MPR121.isNewRelease(ELECTRODE))
        {
         // led_status = false;
         // digitalWrite(LED_BUILTIN, led_status);
          //Serial.println(" nuovo rilascio");

        }
      }
    }
  }
}

void playChimes() 
{
  if( millis() - chimesStartTime < chimesDuration)
  {
    // play chimes 
    Serial.println("\tchimes ON");
  }
  else
  {
    bChimesStatus = false;
    //servo.write( 90 );
    Serial.println("\tchimes OFF");
  }

}

