byte bang;
color c;
long elapsedTime, startTime;
long T = 6000;
byte x, y;
color A = color(255, 0, 0);
color B = color(0, 0, 255);


// SETUP ////////////////////////////////////////////////////
void setup() 
{
  elapsedTime = T;
  c = color (120, 120, 120);
}

// DRAW /////////////////////////////////////////////////////
void draw() 
{
  if( elapsedTime < T )
  {
    elapsedTime = millis() - startTime;
    if( elapsedTime > T )
      elapsedTime = T;
    
    x = byte((elapsedTime * 255) / T);
    y = byte(255 - x);
    
    int yA_red = ((int(red(A))*int(y))>>8);
    int xB_red = ((int(red(B))*int(x))>>8);
    
    println(yA_red+"\t-\t"+xB_red);
    
    int yA_green = ((int(green(A))*y)>>8);
    int xB_green = ((int(green(B))*x)>>8);
    
    int yA_blue = ((int(blue(A))*y)>>8);
    int xB_blue = ((int(blue(B))*x)>>8);

    byte r = byte(yA_red + xB_red);
    byte g = byte(yA_green + xB_green);
    byte b = byte(yA_blue + xB_blue);
    println("r: "+r+";\tg:"+g+";\tb: "+b+";");
    c = color(r, g, b);
  }
  else
  {
    println(" - ");
  }
  
  
  background( c );
  
}

// OTHER ////////////////////////////////////////////////////
void mousePressed()
{
  elapsedTime = 0;
  startTime = millis();
}