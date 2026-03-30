#include "adc_monitor.h"
#include "esp_adc/adc_oneshot.h"
#include "esp_log.h"
#include "esp_timer.h"
static const char *TAG = "ADC_MONITOR";
static adc_oneshot_unit_handle_t adc_handle = NULL;

void adc_monitor_init(void) {
    ESP_LOGI(TAG, "Initializing ADC...");
    
    // Configure ADC unit
    adc_oneshot_unit_init_cfg_t init_config = {
        .unit_id = ADC_UNIT_1,
    };
    
    ESP_ERROR_CHECK(adc_oneshot_new_unit(&init_config, &adc_handle));
    
    // Configure channel (GPIO34 = ADC1_CHANNEL_6)
    adc_oneshot_chan_cfg_t config = {
        .bitwidth = ADC_BITWIDTH_12,      // 12-bit resolution (0-4095)
        .atten = ADC_ATTEN_DB_12,         // Full range: 0-3.3V
    };
    
    ESP_ERROR_CHECK(adc_oneshot_config_channel(adc_handle, ADC_CHANNEL_6, &config));
    
    ESP_LOGI(TAG, "ADC initialized successfully");
}

adc_sample_t adc_read_sample(void) {
    adc_sample_t sample = {0};
    int adc_reading = 0;
    
    // Read raw ADC value
    esp_err_t ret = adc_oneshot_read(adc_handle, ADC_CHANNEL_6, &adc_reading);
    
    if (ret == ESP_OK) {
        sample.raw_adc = adc_reading;
        
        // Convert to millivolts
        // Formula: voltage_mv = (adc_reading / 4095) * 3300 mV
        sample.voltage_mv = (adc_reading / 4095.0f) * 3300.0f;
        
        sample.timestamp_ms = (uint32_t)(esp_timer_get_time() / 1000);
    } else {
        ESP_LOGE(TAG, "ADC read failed!");
    }
    
    return sample;
}