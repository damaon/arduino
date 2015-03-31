char morse[32] = { 0 };
void initializeMorse()
{
  // ASCII code to "binary dot/dash"
  morse[65] = 0b110;
  morse[66] = 0b10111;
  morse[67] = 0b10101;
  morse[68] = 0b1011;
  morse[69] = 0b11;
  morse[70] = 0b11101;
  morse[71] = 0b1001;
  morse[72] = 0b11111;
  morse[73] = 0b111;
  morse[74] = 0b11000;
  morse[75] = 0b1010;
  morse[76] = 0b11011;
  morse[77] = 0b100;
  morse[78] = 0b101;
  morse[79] = 0b1000;
  morse[80] = 0b11001;
  morse[81] = 0b10010;
  morse[82] = 0b1101;
  morse[83] = 0b1111;
  morse[84] = 0b10;
  morse[85] = 0b1110;
  morse[86] = 0b11110;
  morse[87] = 0b1100;
  morse[88] = 0b10110;
  morse[89] = 0b10100;
  morse[90] = 0b10011;
}

const int ledPin = 13;
const int shortMorseValue = 200;
const int longMorseValue = 3 * shortMorseValue;
const int wordBreakMorseValue = 3 * longMorseValue;
const int speaker = 8;

char character;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(speaker, OUTPUT); 
  initializeMorse();
}

void loop()
{
  while (Serial.available())
  {
    character = Serial.read();    
    writeMorseCharDigital(character);
    
    if (character == ' ')
      delay(wordBreakMorseValue);
    else
      delay(shortMorseValue);
  }
}

void writeMorseCharDigital(char c)
{
  if (c < 65 || c > 90) return;
  
  char morseCode = morse[c];
  
  writeMorseCodeDigital(morseCode);
}

void writeMorseCodeDigital(char morseCode)
{
  if (morseCode == 1) return;
  
  writeMorseCodeDigital(morseCode >> 1);
  
  digitalWrite(ledPin, HIGH);
  digitalWrite(speaker, HIGH); 
  
  if ((morseCode & 1) == 1) //dot
    delay(shortMorseValue);
  else // dash
    delay(longMorseValue);
  
  digitalWrite(speaker, LOW);
  digitalWrite(ledPin, LOW);
  delay(shortMorseValue);
}

