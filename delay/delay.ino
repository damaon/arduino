const int button = 13;
const int led = 12;
const unsigned long opoznienie = 1000;
const int rozmiar= 30;
boolean on = true;
unsigned long presses[rozmiar] = { 0 };
int ps = 0;
int psr = 0;
boolean odczyt = true;

void setup(){
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  //obsluga buttona
  unsigned long czas = millis();
  if(digitalRead(button) == HIGH && odczyt){
    Serial.println("Button pressed");
    unsigned long dodaj = czas + opoznienie;
    Serial.println(dodaj);
    presses[(ps++)%rozmiar] = dodaj;
    odczyt = !odczyt;
  }
  else if(digitalRead(button) == LOW && !odczyt){
    presses[(ps++)%rozmiar] = czas + opoznienie;
    odczyt = !odczyt;
  }
  //
  if( presses[psr%rozmiar] && czas > presses[psr%10]){
    Serial.println("Wieksze");
    Serial.println(czas);
    if(on) digitalWrite(led, HIGH);
    else digitalWrite(led, LOW);
    on = !on;
    presses[psr%rozmiar] = 0;
    psr++;
  }
}
