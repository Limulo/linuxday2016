/**
 * Load and Display 
 * 
 * Images can be loaded and displayed to the screen at their actual size
 * or any other size. 
 */

PImage img;  // Declare variable "a" of type PImage
float factor;

int x = 200;
int y = 200;
int r = 100;

boolean bInside = false;

void setup() {
  size(640, 360);
  smooth();
  
  img = loadImage("world.png");  // Load the image into the program  
  factor = 2.0*r / img.height;
  img.resize( int(img.width * factor), int(img.height * factor) );
  
}

void draw() {
  // Displays the image at its actual size at point (0,0)
  background(120);
  
  pushStyle();
  pushMatrix();
  translate(x, y);
  
  noStroke();
  if(bInside)
    fill(255, 0, 0);
  else
    noFill();
  ellipse(0, 0, 2*r, 2*r);
 
  tint(0);
  image(img, -r, -r);
  
  popMatrix();
  popStyle();
}

void mouseMoved()
{
  if(dist(mouseX, mouseY, x, y) < r )
  {
    bInside = true;
  }
  else 
  {
    bInside = false;
  }
}