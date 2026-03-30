#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"esp_log.h"

static const char *TAG = "energy-meter";
int i=0;

void app_main(void)
{
    ESP_LOGI(TAG, "=== Smart Energy Monitor Starting ===");
    ESP_LOGI(TAG, "Initialized System Successfully");

    while(1)
    {
        ESP_LOGI(TAG, "Energy Meter is running... Count: %d", i++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}