int PhotoR = A0;
int sensor_val = 0;

int delta = 0;
int last_val;
int min_v = 1023;
int max_v = 0;

boolean led_on = false;

void setup() 
{
  Serial.begin(9600);
  pinMode( PhotoR, INPUT);
  pinMode(13, OUTPUT);
  digitalWrite(13, led_on);
  last_val = analogRead(PhotoR);
}

void loop() 
{
  sensor_val = analogRead(PhotoR);
  if (sensor_val < min_v)
    min_v = sensor_val;
  if (sensor_val > max_v)
    max_v = sensor_val;
  delta = max_v - min_v;
  Serial.println(delta);
  delay(10);
  
}
