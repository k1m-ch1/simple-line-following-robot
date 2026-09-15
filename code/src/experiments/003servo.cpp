#include "HardwareSerial.h"
#include <Arduino.h>

#define SERVO_PIN PA0
#define FREQ_SERVO 50
#define DUTY_MIN 0.025
#define DUTY_MAX 0.125

#define SERVO_SWEEP_FREQ 0.1f

HardwareTimer timerServo(TIM2);

float t = 0;
void setup() {}

void loop() {
  for (uint8_t i = 0; i < 180 + 1; i++) {
    t = i / 180.0f;
    timerServo.setPWM(1, SERVO_PIN, FREQ_SERVO,
                      ((1 - t) * DUTY_MIN + t * DUTY_MAX) * 100.0f);
    timerServo.resume();
    delay(100);
  }
}
