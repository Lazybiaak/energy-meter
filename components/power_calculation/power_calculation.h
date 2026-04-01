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
void power_calculation_init(void);
void log_power(power_t power);
power_t get_logged_power(uint16_t index);
power_t max_power();
power_t min_power();
power_t average_power();
#endif // POWER_CALCULATION_H