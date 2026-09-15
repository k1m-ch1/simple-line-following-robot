#include <Arduino.h>

#define SERVO_PIN PA0
#define FREQ_SERVO 50

#define DUTY_MIN 2.5f
#define DUTY_MAX 12.5f

#define SWEEP_TIME_MS 5000
#define STEPS 1000

HardwareTimer timerServo(TIM2);

void setup() {
  timerServo.setPWM(1, SERVO_PIN, FREQ_SERVO, DUTY_MIN);
  timerServo.resume();
}

void loop() {
  for (int i = 0; i <= STEPS; i++) {
    float t = i / (float)STEPS;

    float duty = DUTY_MIN + t * (DUTY_MAX - DUTY_MIN);

    timerServo.setPWM(1, SERVO_PIN, FREQ_SERVO, duty);

    delay(SWEEP_TIME_MS / STEPS);
  }

  for (int i = STEPS; i >= 0; i--) {
    float t = i / (float)STEPS;

    float duty = DUTY_MIN + t * (DUTY_MAX - DUTY_MIN);

    timerServo.setPWM(1, SERVO_PIN, FREQ_SERVO, duty);

    delay(SWEEP_TIME_MS / STEPS);
  }
}
