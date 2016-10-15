#define RELAY0 22
#define RELAY1 23
#define RELAY2 24

// SETUP ///////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(9600);
  
  pinMode(RELAY0, OUTPUT);
  digitalWrite(RELAY0, LOW);

  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, LOW);

  pinMode(RELAY2, OUTPUT);
  digitalWrite(RELAY2, LOW);
  
}

// LOOP ////////////////////////////////////////////////////////////
void loop()
{
  if (Serial.available() > 0)
  {
    char c = Serial.read();

    switch (c) 
    {
      case '1':
        digitalWrite(RELAY0, HIGH);
        break;
      case 'q':
        digitalWrite(RELAY0, LOW);
        break;
        
      case '2':
        digitalWrite(RELAY1, HIGH);
        break;
      case 'w':
        digitalWrite(RELAY1, LOW);
        break;
        
      case '3':
        digitalWrite(RELAY2, HIGH);
        break;
      case 'e':
        digitalWrite(RELAY2, LOW);
        break;
        
      default:
        Serial.println("Valore non valido");
        break;
    }
  }
}


