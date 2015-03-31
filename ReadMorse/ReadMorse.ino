char morse[32] = { 0 };
void initializeMorse()
{
morse[6]  = 'A';
morse[23] = 'B';
morse[21] = 'C';
morse[11] = 'D';
morse[3]  = 'E';
morse[29] = 'F';
morse[9]  = 'G';
morse[31] = 'H';
morse[7]  = 'I';
morse[24] = 'J';
morse[10] = 'K';
morse[27] = 'L';
morse[4]  = 'M';
morse[5]  = 'N';
morse[8]  = 'O';
morse[25] = 'P';
morse[18] = 'Q';
morse[13] = 'R';
morse[15] = 'S';
morse[2]  = 'T';
morse[14] = 'U';
morse[30] = 'V';
morse[12] = 'W';
morse[22] = 'X';
morse[20] = 'Y';
morse[19] = 'Z';
}

const int buttonPin = 12;
const int ignoreTimeValue = 200;
const int shortMorseValue = 500;
const int longMorseValue = 3 * shortMorseValue; 

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  initializeMorse();  
}

void loop(){
  
  // read the state of the pushbutton value:
  const char buttonState = digitalRead(buttonPin);
  
  if (buttonState != LOW)
  {
    char letter = getLetter();
    Serial.println();
    Serial.print(letter);
    Serial.print(" ");  
  }
}

unsigned long buttonTime(int pin)
{
  const unsigned char lastButtonState = digitalRead(pin);
  const unsigned long startTime = millis();
  
  while (1)
  {
      const char buttonState = digitalRead(pin);
 
      if (buttonState != lastButtonState)
      {
          const unsigned long endTime = millis();
          const unsigned long stateTime = endTime - startTime;
          
          return stateTime;
      }
  }
}

char getLetter()
{
  
  char morseIndex = 1; 
  unsigned long timeoutStartTime = millis();

  while (true)
  {
    const char buttonState = digitalRead(buttonPin);
    
    if (buttonState == HIGH)
    {
      const unsigned long time = buttonTime(buttonPin);
      
      if (time >= ignoreTimeValue && time < longMorseValue) // dot
      {
        morseIndex = morseIndex << 1;
        morseIndex = morseIndex | 1;
        Serial.print(". ");
      }  
      else if( time >= longMorseValue )// dash
      {
        morseIndex = morseIndex << 1;
        Serial.print("- ");
      }
      
      timeoutStartTime = millis();
    }
    else
    {
      const unsigned long time = millis() - timeoutStartTime;
      
      if (time >= longMorseValue) // delay between single mark
      {
        return morse[morseIndex];
      }
    }
  }
}

