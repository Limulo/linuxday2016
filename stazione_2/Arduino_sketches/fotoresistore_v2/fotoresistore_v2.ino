#define MOD 0.6

int PhotoR = A0;
int sensor_val = 0;

int delta = 0;
int min_v = 1023;
int max_v = 0;
int th;

boolean led_on = false;

void setup() 
{
  Serial.begin(9600);
  pinMode( PhotoR, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, led_on);
}

void loop() 
{
  sensor_val = analogRead(PhotoR);
  if (sensor_val < min_v)
    min_v = sensor_val;
  if (sensor_val > max_v)
    max_v = sensor_val;
  delta = max_v - min_v;
  
  //th = delta*MOD;
  th = 700;
  if (sensor_val < th)
    led_on = true;
  else
    led_on = false;

  digitalWrite(13, led_on);
  Serial.print(sensor_val);
  
  Serial.print('\t'); Serial.print(delta);
  Serial.print('\t'); Serial.println(th);
  
  delay(10);
  
}
