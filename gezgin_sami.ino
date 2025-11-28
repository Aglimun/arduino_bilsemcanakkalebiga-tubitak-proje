#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Adafruit_Sensor.h>

LiquidCrystal_I2C lcd(0x27,16,2); // Bu kodu kullanırken ekranda yazı çıkmaz ise 0x27 yerine 0x3f yazınız !!
int sensorPin = A0;   // Sensörün analog çıkışı A0 pinine bağlı
int sensorValue = 0;  // Ham analog değer
int nemOrani = 0;     // Yüzdelik nem oranı
#define DHTPIN 2         // DHT22 veri pini D2'ye bağlı
#define DHTTYPE DHT22    // Sensör tipi: DHT22
int pot = A1;
DHT dht(DHTPIN, DHTTYPE);
int buzzerPin = 11;
int red = 10;
int green = 9;
int blue = 8;
int pompa = 13;
int potdeger = 0;

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  Serial.begin(9600); 
  dht.begin();            
  Serial.println("DHT22 sensöründen veri okunuyor...");
  Serial.println("YL-69 Toprak Nem Sensörü Başlatıldı");
  pinMode(buzzerPin, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT); 
  pinMode(pompa, OUTPUT);  
  pinMode(pot, INPUT);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  float sic = dht.readTemperature();
  potdeger = analogRead(pot);
  Serial.println(potdeger);
  nemOrani = map(sensorValue, 1023, 0, 0, 100);
/*
  if (nemOrani < 50){
    digitalWrite(buzzerPin, HIGH); 
    digitalWrite(pompa, HIGH);
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Su Pompalaniyor");
    lcd.setCursor(0,1); 
    lcd.print("....Nem Az....");
    delay(4000);                 
    digitalWrite(buzzerPin, LOW);
    digitalWrite(pompa, LOW); 
  }
  else{
    digitalWrite(pompa, LOW);
  }
*/
  if (sic < 15){ 
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);
    digitalWrite(blue, LOW); 
  }else if(sic > 27){
    digitalWrite(red, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(blue, HIGH);
  }
  else{
    digitalWrite(red, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(blue, HIGH);
  }
   
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("Sicaklik");
  lcd.setCursor(0,1); 
  lcd.print(sic);
  lcd.print("'C");
  
  delay(1000);
  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print("T.Nem Orani");
  lcd.setCursor(0,1);
  lcd.print("%");
  lcd.print(nemOrani);
  delay(1000);
  Serial.print("nem:"); Serial.print(nemOrani);
  Serial.print(";sic:"); Serial.print(sic);
  Serial.print(";pot:"); Serial.print(potdeger);
  Serial.print(";pump:"); Serial.println(nemOrani < 50 ? 1 : 0);
  }
