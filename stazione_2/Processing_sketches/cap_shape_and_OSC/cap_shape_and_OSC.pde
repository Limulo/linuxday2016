  /*
* 18 Oct 2016
*/

/* SERIAL *************************************************************************/
import processing.serial.*;
Serial s_port;
boolean bSerialListen = false;

/* OSC ****************************************************************************/
import netP5.*;
import oscP5.*;
OscP5 oscP5;
NetAddress myRemoteLocation;
String IPaddr = "127.0.0.1";
int port = 12000; //this is the receive port. Send port is Receive port + 1

// number of electrodes to plot
final int N_ELECTRODES = 9;

Shape[] shapes;
PFont font;
color bgr;

// SETUP ////////////////////////////////////////////////////////////////////////////
void setup()
{
  size(1024, 960);  
  frameRate(30);
  smooth();
  
  /* SERIAL *************************************************************************/
  println(Serial.list());  
  s_port = new Serial(this, Serial.list()[0], 115200);
  s_port.buffer( 2 ); //every 2 byte call serialEvent
  
  
  /* OSC ****************************************************************************/
  /* start oscP5, listening for incoming messages at port 12000 */
  oscP5 = new OscP5(this, port);
  
  /* myRemoteLocation is a NetAddress. a NetAddress takes 2 parameters,
   * an ip address and a port number. myRemoteLocation is used as parameter in
   * oscP5.send() when sending osc packets to another computer, device, 
   * application. usage see below. for testing purposes the listening port
   * and the port of the remote location address are the same, hence you will
   * send messages back to this sketch.
   */
  myRemoteLocation = new NetAddress( "127.0.0.1", port+1 );
  
  /* OTHER **************************************************************************/
  shapes = new Shape[ N_ELECTRODES ];
  for(int i=0; i<N_ELECTRODES; i++)
  {
    shapes[i] = new Shape(i, 500);
  }
  
  font = loadFont("Monospaced-32.vlw");
  textFont(font, 14);
  bgr = color(0);
}

// DRAW /////////////////////////////////////////////////////////////////////////////
void draw()
{
  background(bgr);
  
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
      
      /* in the following different ways of creating osc messages are shown by example */
      OscMessage myMessage;
      switch( electrodeIndex )
      {
        case 0:
          myMessage = new OscMessage("/note0");
          break;
        case 1:
          myMessage = new OscMessage("/note1");
          break;
        case 2:
          myMessage = new OscMessage("/note2");
          break;
        case 3:
          myMessage = new OscMessage("/note3");
          break;
        default:
          myMessage = new OscMessage("/default");
          break;
      }
      myMessage.add( v );
     
      /*
      if( v == 1 )
      {
        //println("Send OSC: #"+electrodeIndex+" ON;");
        myMessage.add( v );
      }
      else
      {
        //println("Send OSC: #"+electrodeIndex+" OFF;");
        myMessage.add( v );
      }
      */
      
      /* send the message */
      oscP5.send( myMessage, myRemoteLocation );
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
    bgr = color(120);
  }
  else if( key == 'c' || key == 'C')
  {
    s_port.write('c');
    bSerialListen = false;
    bgr = color(0);
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
    text("Serial Communication: ON; Press 'c' to close it.", width/2, 20);
  else
    text("Serial Communication: OFF; Press 'o' to open it.", width/2, 20);
  popStyle();
}