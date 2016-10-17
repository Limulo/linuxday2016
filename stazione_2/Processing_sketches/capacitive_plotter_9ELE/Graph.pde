class Graph
{
  int x, y;
  int w, h;
 
  int N; // numero di valori orizzontali
  int wValue;
  int current;
  
  int[] baseline;
  int[] filtered;
  
  int bestDelta, vDelta, vBase, vFilt;
  
  boolean bTouch;
  
  /* CONTRUCTOR **********************************************************/
  Graph(int _x, int _y, int _w, int _h, int _N )
  {
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    N = _N;
    bTouch = false;
    baseline = new int[N];
    filtered = new int[N];
    
    bestDelta = 0;
    vDelta = 0;
    vBase = 0;
    vFilt = 0;
    
    wValue = w/N;
    
    for(int i=0; i<N; i++)
    {
      baseline[i]=0;
      filtered[i]=0;
    }
    current = 0; 
  }
  
  /* SETTERS *************************************************************/
  void setBase(int _v)
  {
    //println("scrivo Base");
    vBase = _v;
  }
  
  void setFilt(int _v)
  {
    //println("scrivo Filt");
    vFilt = _v;
  }
  
  void setTouch(boolean _v)
  {
    //println("scrivo Touch");
    bTouch = _v;
  }

  /* DRAWS ***************************************************************/
  void draw_all()
  {
    draw_deltas( );
    draw_baseline( );
    draw_filtered( );
    draw_touches( );
    draw_axes_and_texts( ); 
  }
   
  void draw_deltas()
  {
    pushStyle();
    noStroke();
    fill( base, 120 );
    int offset = y;
    for(int i = 0; i < N; i++)
    {
      int delta = baseline[i] - filtered[i];
      rect(i*wValue, filtered[i] + offset, wValue, delta);
    }
    popStyle();
  }
  
  void draw_baseline()
  {
    pushStyle();
    stroke(base);
    strokeWeight(2);

    int offset = y;
    for(int i = 0; i < N; i++)
      line(i*wValue, baseline[i] + offset, (i+1)*wValue, baseline[i] + offset);
   
    popStyle();
  }
  
  void draw_filtered()
  {
    pushStyle();
    stroke(filt);
    strokeWeight(2);
    fill(filt);
    
    int offset = y;
    for(int i = 0; i < N; i++)
      ellipse( (i*wValue)+(wValue/2), filtered[i]+offset, 2, 2);
    
    popStyle();
  }
  
  void draw_axes_and_texts()
  {
    pushStyle();
    stroke(lines);
    strokeWeight(1);
    
    int offset = y;
    line(0, USL+offset, w, USL+offset);
    line(0, LSL+offset, w, LSL+offset);
    line(0, TAR+offset, w, TAR+offset);
    
    textAlign(LEFT);
    text("USL", 10, USL+offset-2);
    text("LSL", 10, LSL+offset-2);
    text("TAR", 10, TAR+offset-2);
    
    text("Base: "+vBase, 10, 20+offset);
    text("Filt: "+vFilt, 10, 40+offset);
    text("Dlta: "+vDelta, 10, 60+offset);
    text("best: "+bestDelta, 10, 80+offset);
    
    textAlign(RIGHT);
    text("Graph 0", w, offset+20);
    
    popStyle();
  }
  
  void draw_touches()
  {
    int r = 30;
    pushStyle();
    stroke( touch );
    if( bTouch )
      fill( touch );
    else 
      noFill();
    int offset = y;
    ellipse(width - r - 5, 45 + offset, r, r);
    popStyle();  
  }
  
  /* UPDATES and OTHERS **************************************************/
  void update() 
  {
    vDelta = vBase - vFilt;
    if( abs(vDelta) > bestDelta ) 
      bestDelta = abs(vDelta);
    
    int v =  (int)map(vBase, 0, 1023, h, 0);
    baseline[current]= v;
    v = (int) map(vFilt, 0, 1023, h, 0);
    filtered[current]= v;

    current++;
    current = current%N;
  }
  
  void reset()
  {
    bestDelta = 0;
  }  
}