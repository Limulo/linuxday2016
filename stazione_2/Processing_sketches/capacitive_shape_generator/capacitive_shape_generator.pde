import processing.serial.*;
Serial s_port;
boolean bSerialListen = false;

// number of electrodes to plot
final int N_ELECTRODES = 9;

Shape[] shapes;

PFont font;


// SETUP ////////////////////////////////////////////////////////////////////////////
void setup()
{
  size(1000, 768);  
  frameRate(30);
  smooth();
  
  println(Serial.list());
  
  s_port = new Serial(this, Serial.list()[0], 115200);
  s_port.buffer( 2 ); //every 2 byte call serialEvent
  
  shapes = new Shape[ N_ELECTRODES ];
  for(int i=0; i<N_ELECTRODES; i++)
  {
    shapes[i] = new Shape(i, 500);
  }
  
  font = loadFont("Monospaced-32.vlw");
  textFont(font, 14);
}

// DRAW /////////////////////////////////////////////////////////////////////////////
void draw()
{
  background(120);
  
  if( bSerialListen ) 
  {
    for(int i=0; i<N_ELECTRODES; i++)
    {
      shapes[i].update();
    }
  } 
  
  draw_other_info();
}
  
// SERIAL EVENT /////////////////////////////////////////////////////////////////////
// serialEvent is called only when we have 2 byte waiting to be red in the buffer.
void serialEvent( Serial s )
{  
  try{
    int addr = s.read() - 128;
    int v = -1;
    
    // Arduino will normally send 6 bytes for each electrod: 
    // * 3 consecutive addresses (numbers from 128 to 255) and 
    // * 3 corresponding values (numbers from 0 to 127);
    //
    // Each pair of addr+value is for describing 
    // * baseline value of the electrode;
    // * filtered value for the electrode;
    // * touch status of the electrode;
    //
    // So, to find what electrode Arduino is talking about we have to
    // divide addr by 3.
    int electrodeIndex = addr / 3;
    
    // For the first 4 electrodes we have to resend data using OSC
    if( electrodeIndex < 4 )
    {
      v = s.read();
      if( v == 1 )
        println("Send OSC: #"+electrodeIndex+" ON;");
      else
        println("Send OSC: #"+electrodeIndex+" OFF;");
    }
    // Then, other 4 electrodes creates shapes on screen
    else if ( electrodeIndex < 8 ) 
    {
      v = s.read();
      if( v == 1 )
        shapes[ electrodeIndex ].setTouch( true );
      else
        shapes[ electrodeIndex ].setTouch( false );
    }
    // The last electrode is used by Arduino to turn ON
    // a relay so we can throw its value away
    else
    {
      v = s.read();      
    }
  }catch(Exception e){
    e.printStackTrace();
  }
}

// KEY PRESSED //////////////////////////////////////////////////////////////////////
void keyPressed()
{
  if (key == 'o' || key == 'O')
  {
    s_port.write('o');
    bSerialListen = true;
  }
  else if( key == 'c' || key == 'C')
  {
    s_port.write('c');
    bSerialListen = false;
  }
  else if (key == 'r' || key == 'R')
  {
    s_port.write('r');
    /*
    for(int i=0; i<N_ELECTRODES; i++)
    {
      graphs[i].reset();
    }
    */
  }
}

// CUSTOM /////////////////////////////////////////////////////////////////////////

void draw_other_info()
{
  pushStyle();
  textAlign(CENTER);
  if( bSerialListen )
    text("Serial: ON", width/2, 20);
  else
    text("Serial: OFF", width/2, 20);
  popStyle();
}