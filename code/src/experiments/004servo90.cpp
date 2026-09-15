#include <Arduino.h>

#define SERVO_PIN PA0

#define SERVO_FREQ 50
#define SERVO_DUTY 7.5f // 1.5 ms / 20 ms = 7.5%

HardwareTimer timerServo(TIM2);

void setup() {
  timerServo.setPWM(1, // TIM2 channel 1
                    SERVO_PIN,
                    SERVO_FREQ, // 50 Hz
                    SERVO_DUTY  // 7.5% = 1.5 ms pulse
  );

  timerServo.resume();
}

void loop() {}
