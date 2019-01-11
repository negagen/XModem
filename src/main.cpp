#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

void setup() {
  Serial.begin(115200);
  SPI.begin();
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
}
