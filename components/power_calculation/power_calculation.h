#ifndef POWER_CALCULATION_H
#define POWER_CALCULATION_H

#include "../adc_monitor/adc_monitor.h"
#include <stdint.h>
typedef struct {
    float voltage_mv; // Voltage in millivolts
    float value; // Power in miliwatts
    float current; // Current in milliamps
    float ref_voltage; // Reference voltage in millivolts
    uint32_t timestamp_ms;
} power_t;

power_t calculate_power(adc_sample_t sample, float ref_voltage);
#endif // POWER_CALCULATION_H