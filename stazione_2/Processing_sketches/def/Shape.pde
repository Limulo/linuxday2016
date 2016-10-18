class Shape
{
  int index;
  int x, y, l, maxL;
  color c;
  float angle;
  
  boolean bTouch;
  
  /* CONTRUCTOR **********************************************************/
  Shape(int _idx, int _maxL )
  {
    index = _idx;
    x = 0;
    y = 0;
    maxL = _maxL;
    c = color( 255, 0, 0 );
    angle = 0.0;
  
    bTouch = false;
  }
  
  /* UPDATE **************************************************************/  
  void update()
  {
    if( bTouch )
    {
      pushStyle();
      pushMatrix();
      translate(x, y);
      rotate( angle );
      stroke( c );
      fill( c );
      
      switch( index )
      {
        case 4:
          rectMode( CENTER );
          rect( 0, 0, l, l);
          break;
          
        case 5:
          ellipse( 0, 0, l, l);
          break;
        
        case 6:
          rectMode( CENTER );
          rect( 0, 0, l, l);
          break;
        
        case 7:
          ellipse( 0, 0, l, l);
          break;
        
        default:
          // do nothing
          break;
      }
      
      
      popMatrix();
      popStyle();
    }
    else
    {
      // do nothing
    }
  }
  
  void setTouch(boolean _v)
  {
    //println("scrivo Touch");
    bTouch = _v;
    if( bTouch )
    {
      x = (int) random(0, width);
      y = (int) random(0, height);
      l = (int) random(30, maxL);
      char r = (char)random(0, 255);
      char g = (char)random(0, 255);
      char b = (char)random(0, 255);
      c = color(r, g, b);
      angle = radians( random(0, 360) );
    }
    else
    {
      // do nothing
    }
  } 
}