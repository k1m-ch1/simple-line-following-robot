#include "config.h"
#include <Arduino.h>
#include <stdint.h>

void setup() {
  for (uint8_t i = 0; i < MOTOR_AMOUNT; i++) {
    pinMode(motorPins[i].in1, OUTPUT);
    pinMode(motorPins[i].in2, OUTPUT);
  }

  for (uint8_t i = 0; i < MOTOR_AMOUNT; i++) {
    digitalWrite(motorPins[i].in1, HIGH);
    digitalWrite(motorPins[i].in2, LOW);
  }
  delay(2000);
  for (uint8_t i = 0; i < MOTOR_AMOUNT; i++) {
    digitalWrite(motorPins[i].in1, LOW);
    digitalWrite(motorPins[i].in2, HIGH);
  }
  delay(2000);

  for (uint8_t i = 0; i < MOTOR_AMOUNT; i++) {
    digitalWrite(motorPins[i].in1, LOW);
    digitalWrite(motorPins[i].in2, LOW);
  }
}

void loop() {}
