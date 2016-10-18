class Button
{
  int x, y, l;
  boolean bInside, bLit;
  
  color black = color(0);
  color lit = color(255, 255, 0);
  
  Button(int _x, int _y, int _l)
  {
    x = _x;
    y = _y;
    l = _l;
    bInside = false;
    bLit = false;
  }
  
  void display()
  {
    pushStyle();
    pushMatrix();
    translate(x, y);
    
    stroke(balck);
    strokeWeight( 8 );
    
    if( bLit )
      fill(lit);
    else
      noFill();
      
    rectMode(CENTER);
    rect( 0, 0, l, l);
    popMatrix();
    popStyle();
  }
  
  void update(int _x, int _y)
  {
    // is mouse inside?
    if( (_x > x-l/2 && _x < x+l/2) && (_y>y-l/2 && _y<y+l/2) )
      bInside = true;
    else
      bInside = false;
      
    if( bInside )
      bLit = !bLit;
    return bLit;
  }
}