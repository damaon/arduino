// digital pin 2 has a pushbutton attached to it. Give it a name:
int lewob = 2;
int gorab = 4;
int prawob = 4;
int dolb = 5;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // make the pushbutton's pin an input:
  pinMode(lewob, INPUT);
  pinMode(gorab, INPUT);
  pinMode(prawob, INPUT);
  pinMode(dolb, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  boolean l = digitalRead(lewob);
  boolean r = digitalRead(prawob);
  boolean t = digitalRead(gorab);
  boolean b = digitalRead(dolb);
  // print out the state of the button:
  Serial.print("lewo");
  Serial.println(l);
    Serial.print("gora");
  Serial.println(t);
    Serial.print("prawo");
  Serial.println(r);
    Serial.print("dol");
  Serial.println(b);
  delay(1000);        // delay in between reads for stability
}
