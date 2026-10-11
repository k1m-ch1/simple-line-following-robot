#ifndef CONFIG_H
#define CONFIG_H

#include "variant_PILL_F103Cx.h"
#include <Arduino.h>
#include <stdint.h>

typedef struct {
  uint8_t in1;
  uint8_t in2;
} MotorPins;

#define MOTOR_AMOUNT 2

const MotorPins motorPins[MOTOR_AMOUNT] = {{PB3, PB4}, {PB6, PB7}};

#define IR_SENSOR_AMOUNT 8

const uint8_t irSensorPins[IR_SENSOR_AMOUNT] = {PA0, PA1, PA2, PA3,
                                                PA4, PA5, PA6, PA7};

#define ANALOG_READ_RESOLUTION 12

typedef struct {
  uint16_t minADC;
  uint16_t maxADC;
} IRConfig;

#define IR_ADC_THRESHOLD 0.5f

const IRConfig defaultIRConfig[IR_SENSOR_AMOUNT] = {
    {3000, 3580}, {2900, 3470}, {2900, 3394}, {3100, 3534},
    {3100, 3516}, {3140, 3537}, {3070, 3500}, {3252, 3636}};

#endif
