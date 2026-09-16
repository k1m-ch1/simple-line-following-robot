#pragma once

#include <stdint.h>

uint32_t frequencyToARR(float frequency, float baseFrequency,
                        uint32_t prescaleFactor);

uint32_t dutyCycleToCCR(float dutyCycle, uint32_t arr);
