

#include<LiquidCrystal.h>
#include<Wire.h>
#include <SoftwareSerial.h>
#define rxPin 2
#define txPin 3
SoftwareSerial sim800(rxPin, txPin);
LiquidCrystal lcd(12, 11, 10, 9, 8, 7); 
int FloatSensor = 14;
int red = 6;
int green = 4;
int relay = 15;
int buzzer = 5;
int buttonState = 1;
void setup() 
{
  Serial.begin(9600);
  sim800.begin(9600);
  Serial.println("SIM800L software serial initialize");
  sim800.println("AT");
  pinMode(FloatSensor, INPUT_PULLUP);
  pinMode (red, OUTPUT);
  pinMode (relay, OUTPUT);
  pinMode (green, OUTPUT);
  pinMode (buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("   Welcome To");
  lcd.setCursor(0, 1);
 lcd.print("  Our Projects");
 delay(3000);
  lcd.setCursor(0, 0);
 lcd.print("REPRESENTED BY:- ");
  lcd.setCursor(0, 1);
  lcd.print("HowToElectronics");
  delay(3000);
  lcd.clear();
 }void loop() 
{
  buttonState = digitalRead(FloatSensor);
 
  if (buttonState == HIGH) 
  {
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(buzzer, LOW);
    digitalWrite(relay, LOW);
    Serial.println("WATER LEVEL - LOW");
    lcd.setCursor(0, 0);
    lcd.print("W-Level:- Normal ");
    lcd.setCursor(0, 1);
    lcd.print("   Motor ON.");
    SendMessageTankNotFull();
  }
  else 
  {
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(buzzer, HIGH);
    digitalWrite(relay, HIGH);
    Serial.println("WATER LEVEL - HIGH");
    lcd.setCursor(0, 0);
    lcd.print("W-Level:- FULL.. ");
    lcd.setCursor(0, 1);
   lcd.print("   Motor OFF"); 
 SendMessageTankFull();
delay(1000);
}
 void SendMessageTankFull()
{
  sim800.println("AT+CMGF=1");
  delay(1000);
  sim800.println((char)26);
  delay(100);
  sim800.println("AT+CMGS=\"+918925203573\"\r");
  delay(1000);
  sim800.println("Water tank is full, please check pump!");
  delay(1000);
}
 
void SendMessageTankNotFull()
{
  sim800.println("AT+CMGF=1");
  delay(1000);
  sim800.println((char)26);
  delay(100);
  sim800.println("AT+CMGS=\"+916380987480\"\r");
  delay(1000);
  sim800.println("Water level monitoring started");
  delay(1000);
}
