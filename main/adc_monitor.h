#ifndef ADC_MONITOR_H
#define ADC_MONITOR_H

#include "esp_err.h"

typedef struct {
    float voltage_mv;
    uint32_t raw_adc;
    uint32_t timestamp_ms;
} adc_sample_t;

// Initialize ADC on GPIO34 (ADC1 Channel 6)
void adc_monitor_init(void);

adc_sample_t adc_read_sample(void);
// Read one sample
esp_err_t adc_monitor_read(adc_sample_t *sample);

#endif