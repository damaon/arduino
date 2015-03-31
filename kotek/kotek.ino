const int c = 9;
const int d = 10;
const int e = 11;
const int f = 12;
const int g = 13;

int dzwiek(int nuta){
  switch(nuta){
    case c : return 131;
    case d : return 147;
    case e : return 165;
    case f : return 175;
    case g : return 196;
  }
}

int buzzer = 3;

int cala = 1000;
int pol = 500;
int cwierc = 250;
int osma = 125;

void nutka(int typ,int l){
  tone(buzzer, dzwiek(typ), l - 50);
  digitalWrite(typ, HIGH);
  delay(l);
  digitalWrite(typ, LOW);
}
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(c, OUTPUT);  
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT); 
}

// the loop routine runs over and over again forever:
void loop() {
  
  nutka(g, cwierc);
  nutka(e, cwierc);
  nutka(e, cwierc);
  nutka(f, cwierc);
  nutka(d, cwierc);
  nutka(d, cwierc);
  nutka(c, osma);
  nutka(e, osma);
  nutka(g, pol);
  
  nutka(g, cwierc);
  nutka(e, cwierc);
  nutka(e, cwierc);
  nutka(f, cwierc);
  nutka(d, cwierc);
  nutka(d, cwierc);
  nutka(c, osma);
  nutka(e, osma);
  nutka(c, pol);
}
