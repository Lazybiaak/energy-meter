#include "power_calculation.h"

power_t calculate_power(float voltage, float ref_voltage) {
    power_t power;
    power.voltage_mv = voltage;
    power.ref_voltage = ref_voltage;
    power.current = power.voltage_mv / 10.0; // Assuming a fixed resistance of 10 ohms for simplicity
    power.value = power.ref_voltage * power.current;
    return power;
}