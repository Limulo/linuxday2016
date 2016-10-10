#define MOD 0.5
#define LED 13
#define PHOTO A0

int sensor_val = 0;

int delta = 0;
int min_v = 1023;
int max_v = 0;
int th;

unsigned long lastTime;
unsigned int T = 3000; 

boolean led_on = false;

// SETUP ---------------------------------------------------------------/
void setup() 
{
  Serial.begin(9600);
  pinMode(PHOTO, INPUT);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, led_on);
  th = 0;
  lastTime = millis();
}

// LOOP ----------------------------------------------------------------/
void loop() 
{
  sensor_val = analogRead(PHOTO);

  if(millis()-lastTime > T)
  {
    min_v = 1023;
    max_v = 0;
    lastTime = millis();
  }

  calibrate( sensor_val );
  
  Serial.print(sensor_val); Serial.print('\t'); 
  Serial.print("[min: "); Serial.print(min_v); Serial.print(" - ");
  Serial.print("max: "); Serial.print(max_v); Serial.print(" ] ");
  Serial.print("dlt: "); Serial.print(delta); Serial.print('\t'); 
  Serial.print("th: "); Serial.println(th);

  if (sensor_val > th)
    led_on = true;
  else
    led_on = false;

  digitalWrite(LED, led_on);
  
  delay(10);
}

// CUSTOM --------------------------------------------------------------/
void calibrate(int v)
{
  if (v < min_v)
    min_v = v;
    
  if (v > max_v)
    max_v = v;
    
  delta = max_v - min_v;

  th = min_v + (delta * MOD);
}

