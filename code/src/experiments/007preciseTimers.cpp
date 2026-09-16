#include "HardwareTimer.h"
#include <Arduino.h>
#include <Utils.h>

const int pwmPin = PB0;

HardwareTimer *MyTimer;
uint32_t channel;

void setup() {
  Serial.begin(115200);
  TIM_TypeDef *Instance =
      (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pwmPin), PinMap_PWM);
  channel =
      STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pwmPin), PinMap_PWM));
  MyTimer = new HardwareTimer(Instance);
  MyTimer->setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pwmPin);
  uint32_t arr = frequencyToARR(50.0f, MyTimer->getTimerClkFreq(), 1);
  MyTimer->setOverflow(arr, TICK_FORMAT);
  MyTimer->setCaptureCompare(channel, dutyCycleToCCR(0.025f, arr),
                             TICK_COMPARE_FORMAT);
  MyTimer->resume();
  Serial.println("timer started");
}

void loop() {}
