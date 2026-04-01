#include "power_calculation.h"
#include "esp_log.h"
#include "esp_vfs_littlefs.h"

static const char *TAG = "POWER_CALCULATION";
power_t calculate_power(adc_sample_t sample, float ref_voltage) {
    power_t power;
    power.voltage_mv = sample.voltage_mv;
    power.ref_voltage = ref_voltage;
    power.current = power.voltage_mv / 10.0; // Assuming a fixed resistance of 10 ohms for simplicity
    power.value = power.ref_voltage * power.current;
    power.timestamp_ms = sample.timestamp_ms;
    log_power(power);
    return power;
}
void power_calculation_init(void){
    // --- 1. CONFIGURATION ---
    esp_vfs_littlefs_conf_t conf = {
        .base_path = "/littlefs",      
        .partition_label = NULL,  
        .format_if_mount_failed = true,
        .dont_mount = false
    };

    // --- 2. INITIALIZATION ---
    esp_err_t ret = esp_vfs_littlefs_register(&conf);

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to initialize LittleFS (%s)", esp_err_to_name(ret));
        return;
    } else {
        ESP_LOGI(TAG, "LittleFS initialized successfully");
    }
}
void log_power(power_t power){
    // --- 3. WRITING DATA ---
    FILE* f = fopen("/littlefs/power.bin", "ab"); 
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for writing");
    } else {
        fwrite(&power, sizeof(power_t), 1, f);
        fclose(f);
        ESP_LOGI(TAG, "File written");
    }
}

power_t get_logged_power(uint16_t index) {
    // --- 4. READING DATA ---
    power_t power;
    FILE* f = fopen("/littlefs/power.bin", "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        // Return a default value or handle the error appropriately
        return (power_t){0};
    } else {
        fseek(f, index * sizeof(power_t), SEEK_SET);
        fread(&power, sizeof(power_t), 1, f);
        fclose(f);
        ESP_LOGI(TAG, "File read");
    }
    return power;
}

power_t max_power() {
    // --- 5. MAX POWER ---
    power_t max_p = {0};
    FILE* f = fopen("/littlefs/power.bin", "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return max_p;
    } else {
        power_t temp;
        while (fread(&temp, sizeof(power_t), 1, f) == 1) {
            if (temp.value > max_p.value) {
                max_p = temp;
            }
        }
        fclose(f);
    }
    return max_p;
}

power_t min_power() {
    // --- 6. MIN POWER ---
    power_t min_p = { .value = FLT_MAX };
    FILE* f = fopen("/littlefs/power.bin", "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return min_p;
    } else {
        power_t temp;
        while (fread(&temp, sizeof(power_t), 1, f) == 1) {
            if (temp.value < min_p.value) {
                min_p = temp;
            }
        }
        fclose(f);
    }
    return min_p;
}

power_t average_power() {
    // --- 7. AVERAGE POWER ---
    power_t avg_p = {0};
    uint32_t count = 0;
    FILE* f = fopen("/littlefs/power.bin", "rb");
    if (f == NULL) {
        ESP_LOGE(TAG, "Failed to open file for reading");
        return avg_p;
    } else {
        power_t temp;
        while (fread(&temp, sizeof(power_t), 1, f) == 1) {
            avg_p.value += temp.value;
            count++;
        }
        fclose(f);
        if (count > 0) {
            avg_p.value /= count;
        }
    }
    return avg_p;
}