import processing.serial.*;
Serial s_port;
boolean bSerialListen = false;

// number of electrodes to plot
final int N_ELECTRODES = 4;

Graph[] graphs;

int USL = 626; //156B
int LSL = 405; //101B
int TAR = 562; //140B

PFont font;

color base  = color(0, 168, 255);
color filt  = color(240, 0, 0);
color touch = color(255, 0, 0);
color lines = color(220, 220, 220, 120);
color bckgr = color(30, 30, 30);


// SETUP ////////////////////////////////////////////////////////////////////////////
void setup()
{
  size(1000, 768);  
  //frameRate(30);
  smooth();
  
  println(Serial.list());
  
  s_port = new Serial(this, Serial.list()[0], 115200);
  s_port.buffer( 2 ); //every 2 byte call serialEvent

  int hGraph = height / N_ELECTRODES;
  
  graphs = new Graph[ N_ELECTRODES ];
  for(int i=0; i<N_ELECTRODES; i++)
  {
    graphs[i] = new Graph(i, 0, hGraph*i, width, hGraph, 100);
  }
  
  USL = (int)map(USL, 0, 1023, hGraph, 0);
  LSL = (int)map(LSL, 0, 1023, hGraph, 0);
  TAR = (int)map(TAR, 0, 1023, hGraph, 0);
  
  font = loadFont("Monospaced-32.vlw");
  textFont(font, 14);
}

// DRAW /////////////////////////////////////////////////////////////////////////////
void draw()
{
  background(bckgr);
  
  if( bSerialListen ) 
  {
    for(int i=0; i<N_ELECTRODES; i++)
    {
      graphs[i].draw_all();
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
    
    // what graph?
    int graphIndex = addr / 3; //each graph uses 3 addresses and three values
    
    if( graphIndex < N_ELECTRODES )
    {
      switch( addr % 3) {
        case 0:
          v = s.read() * 8;
          //print("#" + addr + ", " + v + "; ");
          graphs[ graphIndex ].setBase( v );
          break;
          
        case 1:
          v = s.read() * 8;
          //print("#" + addr + ", " + v + "; ");
          graphs[ graphIndex ].setFilt( v );
          break;
          
        case 2:
          v = s.read();
          //print("#" + addr + ", " + v + "; ");
          
          if( v == 1 )
            graphs[ graphIndex ].setTouch( true );
          else
            graphs[ graphIndex ].setTouch( false );
    
          graphs[ graphIndex ].update();
                 
          break;
        default:
          // do nothing
          break;
      }
    }
  }catch(Exception e){
    e.printStackTrace();
  }
  
  // in case we want to read less than 9 electrodes, we have to
  // flush all the byte from other electrodes
  int remaining_electrodes = 9-N_ELECTRODES;
  for(int i=0;i<remaining_electrodes*6; i++)
  {
    int b = s.read();
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