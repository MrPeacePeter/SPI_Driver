#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "SPI_Drv.h"

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

    uint8_t tx_buf[4] = {0xAA, 0x55, 0x12, 0x34};
    uint8_t rx_buf[4] = {0};

    while (1)
    {
        ret = spi_transceive(tx_buf, rx_buf, sizeof(tx_buf));
        if (ret == ESP_OK)
        {
            ESP_LOGI(TAG,
                     "RX: %02X %02X %02X %02X",
                     rx_buf[0], rx_buf[1], rx_buf[2], rx_buf[3]);
        }
        else
        {
            ESP_LOGE(TAG, "SPI transfer failed (%s)", esp_err_to_name(ret));
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}