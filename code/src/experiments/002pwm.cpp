#include <Arduino.h>

#define FREQ_SERVO 50
#define DUTY_CYCLE_SERVO 0.1f

#define FREQ_MOTOR 20000
#define DUTY_CYCLE_MOTOR 0.5f

#define SERVO_PIN PA0

#define MOTOR_PIN PB7

// PB7 | TIM4_CH2               |

HardwareTimer timerServo(TIM2);
HardwareTimer timerMotor(TIM4);

void setup() {
  timerServo.setPWM(1,                     // TIM2 channel 1
                    SERVO_PIN,             // pin
                    FREQ_SERVO,            // frequency
                    DUTY_CYCLE_SERVO * 100 // duty %
  );
  timerServo.resume();

  timerMotor.setPWM(2, MOTOR_PIN, FREQ_MOTOR, DUTY_CYCLE_MOTOR * 100);

  timerMotor.resume();
}

void loop() {}
