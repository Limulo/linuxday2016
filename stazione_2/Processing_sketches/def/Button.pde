class Button
{
  int x, y, r;
  boolean bInside, bLit;
  
  color black = color(0);
  color lit = color(255, 255, 0);
  
  PImage img;  // Declare variable "a" of type PImage
  float factor;
  
  Button(int _x, int _y, int _r)
  {
    x = _x;
    y = _y;
    r = _r;
    bInside = false;
    bLit = false;
    
    img = loadImage("world.png");  // Load the image into the program  
    factor = 2.0*r / img.height;
    img.resize( int(img.width * factor), int(img.height * factor) );
    
  }
  
  void display()
  {
    pushStyle();
    pushMatrix();
    translate(x, y);
    
    //stroke(black);
    //strokeWeight( 8 );
    
    noStroke();
    
    if( bLit )
      fill(lit);
    else
      noFill();
      
    ellipse(0, 0, 2*r, 2*r);
 
    tint(0);
    image(img, -r, -r);  

    popMatrix();
    popStyle();
  }
  
  boolean update(int _x, int _y)
  {
    // is mouse inside?
    //if( (_x > x-l/2 && _x < x+l/2) && (_y>y-l/2 && _y<y+l/2) )
    if( dist(x, y, _x, _y)<r )
      bInside = true;
    else
      bInside = false;
      
    if( bInside )
      bLit = !bLit;
    return bLit;
  }
}