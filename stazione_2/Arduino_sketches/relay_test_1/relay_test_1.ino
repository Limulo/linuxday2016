#define RELAY 8

void setup() 
{
  Serial.begin(9600);
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  
}

void loop()
{
  if (Serial.available() > 0)
  {
    char input = Serial.read();
    if(input == 'a')
      digitalWrite(RELAY, HIGH);
    else if (input == 's')
      digitalWrite(RELAY, LOW);
    else
      Serial.println("Valore non valido");
  }
}


