const int b1 = 4;
const int b2 = 5;
const int b3 = 6;

volatile boolean byl1 = false;
volatile boolean byl2 = false;
volatile boolean byl3 = false;
volatile boolean bylHigh1 = false;
volatile boolean bylChange0 = true;


void risingInt1(){
  Serial.println("SPAM");
  if(bylChange0){
    Serial.println("RisingInt1");
    bylHigh1 = true;
    bylChange0 = false; 
    if (digitalRead(b1) == HIGH){
      byl1 = true;
      Serial.println("HIGH1");
    }else if(digitalRead(b2) == HIGH){
      byl2 = true;
      Serial.println("HIGH2");
    }else if (digitalRead(b3) == HIGH){
       byl3 = true;
       Serial.println("HIGH3");
    }   
  }
}

void changeInt0(){  
  if(bylHigh1){
    Serial.println("ChangeInt0");
    if(byl1){
      Serial.println("Byl 1");
      byl1 = false;
    }else if(byl2){
      Serial.println("Byl 2");
      byl2 = false;
    }else if(byl3){
      Serial.println("Byl 3");
      byl3 = false;
    }else{
      Serial.println("NIC nie bylo - kod jest zjebany");
    }
    bylChange0 = true;
    bylHigh1 = false;
  } 
  
}


void setup() { 
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(b3, INPUT);
  attachInterrupt(1, risingInt1, HIGH);
  attachInterrupt(0, changeInt0, LOW);
  Serial.begin(115200); 
}

void loop(){
  delay(100);
  //krec sie krec!
}
