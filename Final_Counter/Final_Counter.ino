#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define SDAPin A4 // Data pin
#define SCLPin A5 // Clock pin
// #define trigPin 2
// #define echoPin 3

const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 6;
const int echoPin2 = 7;
int count = 0;
bool person_arrived, person_left;
LiquidCrystal_I2C lcd=LiquidCrystal_I2C(0x27,16,2);
long duration;
int distance1;
int distance2;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();

}
 // begin(16,2);
 // lcd.print("The # of people inside:");
 // lcd.setCursor(0,1);
 
void loop() {
  // measures the distance1 in cm
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  // prints the distance1 in cm
  duration = pulseIn(echoPin1, HIGH);
  distance1 = (duration*.0343)/2;
  // Serial.print("distance1: ");
  // Serial.println(distance1);
  delay(100);

  // measures the distance1 in cm
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  // prints the distance1 in cm
  duration = pulseIn(echoPin2, HIGH);
  distance2 = (duration*.0343)/2;
  // Serial.print("distance2: ");
  // Serial.println(distance2);
  delay(100);

  if(distance1<=104 && not person_arrived)
  {
    count = count + 1;
    person_arrived = true;
    Serial.println("person is entering");
    Serial.print("count = ");
    Serial.println(count);
  }
  else if(distance1>104 && person_arrived)
  {
    person_arrived = false;
    Serial.println("person has entered");
    Serial.print("count = ");
    Serial.println(count);
  }

  if(distance2<=104 && not person_left && count != 0)
  {
    count = count - 1;
    person_left = true;
    Serial.println("person is leaving");
    Serial.print("count = ");
    Serial.println(count);
    Serial.println(person_left);
  }
  if(distance2>104 && person_left)
  {
    person_left = false;
    Serial.println("person has left");
    Serial.print("count = ");
    Serial.println(count);
    Serial.println(person_left);
   }
  if(count>=5)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Please Wait...");
  }
  else
  {
    lcd.setCursor(0,0);
    lcd.print("The next customer");
    lcd.setCursor(0,1);
    lcd.print("may enter. Please");
    lcd.setCursor(0,2);
    lcd.print("enter one at a time.");
  }
}
