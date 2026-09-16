#include "HardwareTimer.h"
#include <Arduino.h>
#include <Utils.h>

const int pwmPin = PB0;

HardwareTimer *MyTimer;
uint32_t channel;
uint32_t arr;
uint32_t prescalar = 8;

void setup() {
  Serial.begin(115200);
  TIM_TypeDef *Instance =
      (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(pwmPin), PinMap_PWM);
  channel =
      STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(pwmPin), PinMap_PWM));
  MyTimer = new HardwareTimer(Instance);
  MyTimer->setMode(channel, TIMER_OUTPUT_COMPARE_PWM1, pwmPin);
  MyTimer->setPrescaleFactor(prescalar);
  arr = frequencyToARR(50.0f, MyTimer->getTimerClkFreq(), prescalar);
  MyTimer->setOverflow(arr, TICK_FORMAT);

  /*
  float t = 90.f / 180.0f;
  MyTimer->setCaptureCompare(
      channel, dutyCycleToCCR((1 - t) * 0.025f + t * 0.1250f, arr),
      TICK_COMPARE_FORMAT);

  MyTimer->resume();
  */
}

void loop() {
  for (uint8_t i = 0; i < 180; i++) {
    float t = i / 180.0f;
    MyTimer->setCaptureCompare(
        channel, dutyCycleToCCR((1 - t) * 0.025f + t * 0.1250f, arr),
        TICK_COMPARE_FORMAT);

    MyTimer->resume();
    Serial.printf("angle: %d\r\n", i);
    delay(10);
  }
}
