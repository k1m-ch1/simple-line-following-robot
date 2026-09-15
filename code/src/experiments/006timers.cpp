#include <Arduino.h>

const int pwmPin = PB0;

HardwareTimer *MyTimer;
uint32_t channel;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial interface started");

  TIM_TypeDef *Instance =
      (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pwmPin), PinMap_PWM);

  channel =
      STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pwmPin), PinMap_PWM));

  Serial.printf("timer: %p, channel: %lu\r\n", Instance, channel);

  MyTimer = new HardwareTimer(Instance);

  Serial.println("hardware timer initialized");

  MyTimer->setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pwmPin);

  Serial.println("set mode done");

  MyTimer->setOverflow(25000, HERTZ_FORMAT);

  Serial.println("set overflow done");

  MyTimer->setCaptureCompare(channel, 50, PERCENT_COMPARE_FORMAT);
  // TODO: use TICK_COMPARE_FORMAT: Sets the duty cycle using raw timer clock
  // ticks (useful for precise timing).

  Serial.println("going to resume timer");

  MyTimer->resume();

  Serial.println("timer started");
}

void loop() {}
