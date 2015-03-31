/*
  LiquidCrystal Library - Hello World
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hello World!" to the LCD
 and shows the time.
 
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 
 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int echoPin = 8;
const int trigPin = 9;
const int LDR = 2;

int statusSwiatlaPrev = -1;
int statusSwiatla = 0;
const int minSwiatlo = 600;
const int maxSwiatlo = 700;

long duration, cm;
<
const int buzzerPin = 6;
const int odlegloscDrzwiczek = 55;
boolean zamknieta = true;

void setup() {
  pinMode(LDR, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Odleglosc w cm:");
  Serial.begin(9600);
}

void loop() {

 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(5); 
 
 digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  cm = duration / 58.2;
 
  if( cm < odlegloscDrzwiczek && zamknieta ){
    zamknieta = false;
    Serial.println("Lodówka została otwarta!");
    // send info to server
  }
  if( cm > odlegloscDrzwiczek && !zamknieta ){
    zamknieta = true;
    Serial.println("Lodówka zamknięta!");
    //
  }
  
  int swiatlo = analogRead(LDR);
  
  
  if( swiatlo < minSwiatlo ){
    statusSwiatla = 0;
  }
  else if (swiatlo > maxSwiatlo){
    statusSwiatla = 2;
  }
  else{
    statusSwiatla = 1;
  }
  
  if(statusSwiatla != statusSwiatlaPrev){
    if( swiatlo < minSwiatlo ){
      Serial.println("Ciemność, widzę ciemność!");
    }
    else if (swiatlo > maxSwiatlo){
      Serial.println("Oświetlenie jest w porządku :)");
    }
    else{
      Serial.println("Czuję się nazbyt oświetlony...");
    }
    statusSwiatlaPrev = statusSwiatla;
  }   
   
  if( !zamknieta ) tone(buzzerPin, 100, 100);
  
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print("        ");
  // print the number of seconds since reset:
  lcd.setCursor(0, 1);
  lcd.print(cm);
  delay(500);
}

