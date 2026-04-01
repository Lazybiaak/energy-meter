#ifndef POWER_CALCULATION_H
#define POWER_CALCULATION_H


typedef struct {
    float voltage_mv; // Voltage in millivolts
    float value; // Power in miliwatts
    float current; // Current in milliamps
    float ref_voltage; // Reference voltage in millivolts
} power_t;

power_t calculate_power(float voltage, float ref_voltage);
#endif // POWER_CALCULATION_H