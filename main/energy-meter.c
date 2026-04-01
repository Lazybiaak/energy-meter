#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "adc_monitor.h"
#include "power_calculation.h"

static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "=== Smart Energy Monitor Starting ===");
    
    // Initialize ADC
    adc_monitor_init();
    
    // Initialize power calculation (including LittleFS)
    power_calculation_init();
    
    ESP_LOGI(TAG, "Starting ADC sampling...");
    
    while (1) {
        adc_sample_t sample = adc_read_sample();
        power_t power = calculate_power(sample, 3300.0f); // Using 3.3V as reference voltage

        printf("Raw: %4lu | Voltage: %.2f mV \nCurrent: %.2f mA | Power: %.2f W \nMax-Power: %.2f W | Min-Power: %.2f W \nAverage-Power: %.2f W\n",
                 sample.raw_adc, sample.voltage_mv, power.current, power.value/1000.0f, max_power().value/1000.0f, min_power().value/1000.0f, average_power().value/1000.0f);

        vTaskDelay(pdMS_TO_TICKS(1000));  // Read once per second
    }
}   