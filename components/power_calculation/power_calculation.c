#include "power_calculation.h"

power_t calculate_power(adc_sample_t sample, float ref_voltage) {
    power_t power;
    power.voltage_mv = sample.voltage_mv;
    power.ref_voltage = ref_voltage;
    power.current = power.voltage_mv / 10.0; // Assuming a fixed resistance of 10 ohms for simplicity
    power.value = power.ref_voltage * power.current;
    power.timestamp_ms = sample.timestamp_ms;
    return power;
}