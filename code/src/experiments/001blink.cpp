#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  pinMode(PC13, OUTPUT);
}

void loop() {
  digitalWrite(PC13, HIGH);
  Serial.println("led is on");
  delay(1000);
  digitalWrite(PC13, LOW);
  Serial.println("led is off");
  delay(1000);
}
