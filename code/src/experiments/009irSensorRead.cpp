#include "config.h"
#include "wiring_analog.h"
#include "wiring_constants.h"
#include <Arduino.h>
#include <stdint.h>

const IRConfig *irConfig = defaultIRConfig;

uint16_t irThresholdValue[IR_SENSOR_AMOUNT];

void setup() {
  for (uint8_t i = 0; i < IR_SENSOR_AMOUNT; i++) {
    pinMode(irSensorPins[i], INPUT_ANALOG);
    irThresholdValue[i] = (irConfig[i].minADC * IR_ADC_THRESHOLD +
                           (1 - IR_ADC_THRESHOLD) * irConfig[i].maxADC);
  }

  Serial.begin(115200);
  analogReadResolution(ANALOG_READ_RESOLUTION);
}

void loop() {
  uint16_t irSensorValues[IR_SENSOR_AMOUNT];
  for (uint8_t i = 0; i < IR_SENSOR_AMOUNT; i++) {
    irSensorValues[i] = analogRead(irSensorPins[i]);
  }

  for (uint8_t i = 0; i < IR_SENSOR_AMOUNT; i++) {
    uint8_t reading = irSensorValues[i] < irThresholdValue[i];

    // Serial.printf(" %d(%d, %d)", irSensorValues[i], reading,
    // irThresholdValue[i]);
    Serial.printf(" %d", reading);
    if (i < IR_SENSOR_AMOUNT - 1) {
      Serial.print(",");
    }
  }
  Serial.println();
  delay(100);
}
