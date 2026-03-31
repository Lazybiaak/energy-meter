#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "adc_monitor.h"

static const char *TAG = "MAIN";

void app_main(void) {
    ESP_LOGI(TAG, "=== Smart Energy Monitor Starting ===");
    
    // Initialize ADC
    adc_monitor_init();
    
    ESP_LOGI(TAG, "Starting ADC sampling...");
    
    while (1) {
        adc_sample_t sample = adc_read_sample();
        printf("Raw: %4lu | Voltage: %.2f mV\n",
                 sample.raw_adc, sample.voltage_mv);
        
        vTaskDelay(pdMS_TO_TICKS(1000));  // Read once per second
    }
}   