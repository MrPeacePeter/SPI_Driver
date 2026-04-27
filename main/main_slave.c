#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "SPI_Drv.h"

static const char *TAG = "SLAVE";

void app_main(void)
{
    esp_err_t ret;

    spi_config_t spi_cfg = {
        .role      = SPI_ROLE_SLAVE,
        .mode      = 0,   // Deve ser o mesmo do Master
        .bit_order = 0    // Deve ser o mesmo do Master
    };

    ret = spi_open(&spi_cfg);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open SPI (%s)", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "SPI Slave started");

    uint8_t tx_buf[4] = {0xDE, 0xAD, 0xBE, 0xEF};
    uint8_t rx_buf[4] = {0};

    while (1)
    {
        ESP_LOGI(TAG, "Waiting for SPI master...");

        ret = spi_transceive(tx_buf, rx_buf, sizeof(tx_buf));
        if (ret == ESP_OK)
        {
            ESP_LOGI(TAG,
                     "RX: %02X %02X %02X %02X",
                     rx_buf[0], rx_buf[1], rx_buf[2], rx_buf[3]);
        }
        else
        {
            ESP_LOGE(TAG, "SPI receive failed (%s)", esp_err_to_name(ret));
        }
    }
}