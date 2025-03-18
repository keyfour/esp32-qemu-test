#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "esp_log.h"

static const char *TAG = "SINGLE_CORE_TEST";

void app_main(void)
{
    ESP_LOGI(TAG, "Starting minimal single-core firmware test");

    // Get core ID using xPortGetCoreID() from FreeRTOS
    uint32_t core_id = xPortGetCoreID();
    ESP_LOGI(TAG, "Running on core: %d", core_id);

    // Check single core configuration
    #if CONFIG_FREERTOS_UNICORE
    ESP_LOGI(TAG, "System configured for single core operation");
    #else
    ESP_LOGI(TAG, "System configured for dual core, but we're forcing single core operation");
    // You can add additional core pinning here if needed
    #endif

    /* Print chip information */
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);
    ESP_LOGI(TAG, "ESP32 chip with %d CPU cores, WiFi%s%s",
            chip_info.cores,
            (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
            (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    ESP_LOGI(TAG, "Silicon revision: %d", chip_info.revision);

    ESP_LOGI(TAG, "%dMB %s flash", spi_flash_get_chip_size() / (1024 * 1024),
            (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded" : "external");

    /* Simple delay loop */
    for (int i = 10; i >= 0; i--) {
        ESP_LOGI(TAG, "Restarting in %d seconds...", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    ESP_LOGI(TAG, "Restarting now.");
    fflush(stdout);
    esp_restart();
}
