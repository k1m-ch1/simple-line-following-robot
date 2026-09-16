#pragma once

#include <stdint.h>

uint32_t frequencyToARR(float frequency, float baseFrequency,
                        uint32_t prescaleFactor) {
  // NOTE: this is to be used when we do a setOverflow, because ARR correspond
  // to the overflow value
  return (baseFrequency / (prescaleFactor * frequency) - 1);
}

uint32_t dutyCycleToCCR(float dutyCycle, uint32_t arr) {
  // assume that the dutyCycle is normalized to be in between 0 and 1
  return dutyCycle * (arr + 1);
}
