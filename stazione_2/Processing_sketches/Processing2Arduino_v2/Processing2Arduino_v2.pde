import processing.serial.*;

Serial myPort;
boolean lit = false;

color base = color(200, 200, 0);
color pressed = color(120, 0, 120);

void setup()
{
  size(640, 480);
  background(120);
  
  //println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
  
}

void draw()
{   
  noStroke();
  if(lit)
    fill(pressed);
  else
    fill(base);
  rect(50, 50, 80, 80);
  
  /*
  while( myPort.available() > 0)
  {
    char c = char(myPort.read() );
    print(c);
  }
  */
}
void mousePressed()
{
  if((isInRange(mouseX, 50, 130)) && (isInRange(mouseY, 50, 130)))
  {
    if(lit)
    {
      lit = false;
      myPort.write('0');
    }
    else
    {
      lit = true;
      myPort.write('1');
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