#include "config.h"
#include "wiring_constants.h"
#include <Arduino.h>
#include <stdint.h>

void setup() {
  for (uint8_t i = 0; i < MOTOR_AMOUNT; i++) {
    pinMode(irSensorPins[i], INPUT_ANALOG);
  }
  Serial.begin(115200);
}

void loop() {
  Serial.println("hello");
  delay(1000);
}
