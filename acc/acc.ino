#include <TinkerKit.h>
#include <math.h>

const int red = 9;
const int green = 10;
const int button = 7;
// obsluga akce... - trudne slowo dletego "zyro" dla zmyłki
TKAccelerometer zyro(I1, I0);

void setup() {                
  pinMode(red, OUTPUT);  
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);  
}

boolean losujKolor = true;
// kolory wysolowane
int redColor = 0;
int greenColor = 0;
// kolory ustawione przez uzytkownika
float redU = 0;
float greenU = 0;

//zeby nie przedobrzyc
float mocKoloru(float moc){
  if( moc < 0) moc = 0;
  if(moc > 255) moc = 255;
  return moc;
}
// defniujemy kiedy kolory sa podobne:
// Ten akcelerometr jest jakiś mało precyzyjny dletego ustawiam na 30
boolean podobneKolory(int k1, int k2){
  return abs(k1 - k2) <  30;
}

//mruganie diodami, kiedy ustawimy podobne kolory
void mrugaj(){
  digitalWrite(green, LOW);
  digitalWrite(red, LOW);
  for(int i = 0; i < 20; i++){
    if( i % 2){
      digitalWrite(red, HIGH);
      digitalWrite(green, LOW);
    }else{
      digitalWrite(green, HIGH);
      digitalWrite(red, LOW);
    }
    delay(100);
  }
}

boolean showColor = true;
void loop() {
  delay(1);
  //wyswietlanie diody
  if (losujKolor) {
     redColor = random(256);
     greenColor = random(256);
     redU = random(256);
     greenU = random(256);
     Serial.print("redColor :");
     Serial.println(redColor);
     Serial.print("greenColor :");
     Serial.println(greenColor);
     losujKolor = false;
  }else{
    //zgaduj ten kolor
    if(showColor){
      analogWrite(red, redColor);
      analogWrite(green, greenColor);
      delay(1000);
      showColor = false;
    }else{
        analogWrite(red, (int)redU);
        analogWrite(green, (int)greenU);
        float xmove = zyro.readXinG()*30;
        float ymove = zyro.readYinG()*30;
        Serial.print("xmove: ");
        Serial.println(xmove);
        Serial.print("ymove: ");
        Serial.println(ymove);
        if (abs(xmove) > abs(ymove)){
          Serial.println("Ruch po osi X");
          redU = mocKoloru(redU + xmove);          
        } else{
          Serial.println("Ruch po osi Y");
          greenU = mocKoloru(greenU + ymove);          
        }  
        Serial.print("  Red: "); Serial.println(redColor - redU);
        Serial.print("Green: "); Serial.println(greenColor - greenU);        
        if( podobneKolory(greenColor, greenU) && podobneKolory(redU, redColor)){
          Serial.println("Gratulacje zgadles kolor");
          mrugaj();
          losujKolor = true;
          showColor = true;
        }
        if ( digitalRead(button) == HIGH){
          Serial.println("Button wcisniety");
          showColor = true;
        }
    }
  }

}
