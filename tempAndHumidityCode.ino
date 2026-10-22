#include <LiquidCrystal.h>
#include <Arduino.h>
#include "Adafruit_SHTC3.h"

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();

//#define PIN_A0   (14)
const int sensorPin = A0; //14
//const int sensorPin = 14; //A0

const float baselineTemp=25; // Degrees C

int switchState = 0;
int prevSwitchState = 0;
int reply;
void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  //DDRC &=~(1<<DDC1);
 // ADCSRA|=0x80; //1000 0000
  pinMode(sensorPin, INPUT);
  DDRB|=0x20; //0010 0000
  DDRB|=0x2;//configure PB1 as output
  //PORTB|=0x20;
  shtc3.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
  //int sensorVal = analogRead(sensorPin);

  sensors_event_t humidity, temp;
  shtc3.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  /*float voltage = (sensorVal/1024.0)* 5.0;
  Serial.print(", Volts: ");
  Serial.print(voltage);

  Serial.print(", degrees C: ");

  float temperatureC = (voltage -.5) * 100;
  Serial.println(temperatureC);*/
  float temperatureF =  (temp.temperature * 9/5) + 32;
  int temperatureFint=int(temperatureF);
  if(temperatureFint>79){
    PORTB|=0x2;
    //delay(500);
  }
  else{
    PORTB&=~0x2;
  }
  delay(10);
  lcd.setCursor(0, 0);
  lcd.print("Temp: "+String(temperatureFint)+" deg F");
  lcd.setCursor(0, 1);
  lcd.print("Humidity :"+String(humidity.relative_humidity)+"%");
  //PORTB&=~0x20;
  delay(1000);
  //PORTB|=0x20;
  //delay(1500);*/
}
