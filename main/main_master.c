#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "SPI_Drv.h"

#define SPI_MAX_BUFFER_SIZE 32

static const char *TAG = "MASTER";

void app_main(void)
{
    esp_err_t ret;

    spi_config_t spi_cfg = {
        .role      = SPI_ROLE_MASTER,
        .mode      = 0,              // SPI Mode 0 (CPOL=0, CPHA=0)
        .bit_order = 0,              // 0 = MSB first
        .clock_hz  = 1 * 1000 * 1000 // 1 MHz
    };

    ret = spi_open(&spi_cfg);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open SPI (%s)", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "SPI Master started");

    uint8_t tx_buf[SPI_MAX_BUFFER_SIZE] = "Master - Test";
    uint8_t rx_buf[SPI_MAX_BUFFER_SIZE] = {0};

    while (1)
    {
        ESP_LOGI(TAG, "TX Texto: %s", tx_buf);
        
        ret = spi_transceive(tx_buf, rx_buf, sizeof(tx_buf));
        if (ret == ESP_OK)
        {
            ESP_LOGI(TAG, "RX Texto: %s", rx_buf);
        }
        else
        {
            ESP_LOGE(TAG, "SPI transfer failed (%s)", esp_err_to_name(ret));
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}