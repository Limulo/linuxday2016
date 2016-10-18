class Graph
{
  int index;
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
  Graph(int _idx, int _x, int _y, int _w, int _h, int _N )
  {
    index = _idx;
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
    
    for(int i = 0; i < N; i++)
    {
      int delta = baseline[i] - filtered[i];
      rect(i*wValue, filtered[i] + y, wValue, delta);
    }
    popStyle();
  }
  
  void draw_baseline()
  {
    pushStyle();
    stroke(base);
    strokeWeight(2);

    for(int i = 0; i < N; i++)
      line(i*wValue, baseline[i] + y, (i+1)*wValue, baseline[i] + y);
   
    popStyle();
  }
  
  void draw_filtered()
  {
    pushStyle();
    stroke(filt);
    strokeWeight(2);
    fill(filt);

    for(int i = 0; i < N; i++)
      ellipse( (i*wValue)+(wValue/2), filtered[i]+y, 2, 2);
    
    popStyle();
  }
  
  void draw_axes_and_texts()
  {
    pushStyle();
    stroke(lines);
    strokeWeight(1);

    line(0, USL+y, w, USL+y);
    line(0, LSL+y, w, LSL+y);
    line(0, TAR+y, w, TAR+y);
    
    textAlign(LEFT);
    text("USL", 10, USL+y-2);
    text("LSL", 10, LSL+y-2);
    text("TAR", 10, TAR+y-2);
    
    text("Base: "+vBase+"; Filt: "+vFilt+ "; Dlta: "+vDelta+ "; best: "+bestDelta, 10, 20+y);
    //text("Base: "+vBase, 10, 20+y);
    //text("Filt: "+vFilt, 10, 40+y);
    //text("Dlta: "+vDelta, 10, 60+y);
    //text("best: "+bestDelta, 10, 80+y);
    
    textAlign(RIGHT);
    text("ELECTRODE "+index, w, y+20);
    
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

    ellipse(width - r - 5, 45 + y, r, r);
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