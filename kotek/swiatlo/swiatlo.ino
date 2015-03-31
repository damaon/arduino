
int diodaPin = 6;
int potPin = 0;     // przypisujemy do zmiennej numer wejścia analogowego
int pot;            // zmienna w której będziemy zapisywać "wartość" potencjometru
int sila;        // zmienna w której będziemy zapisywać szybkość migania
int ma_port = 2;
int ma_ps = 5000;
int ma = 5000;
int mi_port = 4;
int mi_ps = 0;
int mi = 0;
void setup() {
  Serial.begin(9600);
  pinMode(mi_ps, INPUT);
  pinMode(ma_ps, INPUT);
  pinMode(diodaPin, OUTPUT);
}
 
void loop() {
  ma_ps = digitalRead(ma_port);
  mi_ps = digitalRead(mi_port);
  pot = analogRead(potPin);     // odczytujemy A0 i zapisujemy w zmiennej pot
  //Serial.println(pot);
  
  if( ma_ps == HIGH){
    ma = pot;
    Serial.println(pot);
  }
  if( mi_ps == HIGH){
    mi = pot;
    Serial.println(pot);
  }
  
  sila = map(pot, mi, ma, 0, 255);
  if( pot < mi){
  digitalWrite(diodaPin, LOW);
  }
  else if ( pot > ma ){
  digitalWrite(diodaPin, HIGH);
  }
  else{
    //Serial.println(sila);
    analogWrite(diodaPin, sila);
  }             // przerwa zależna od położenia potencjometru
}
