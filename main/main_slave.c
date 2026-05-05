#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "SPI_Drv.h"

#define SPI_MAX_BUFFER_SIZE 32

static const char *TAG = "SLAVE";

void app_main(void)
{
    esp_err_t ret;

    spi_config_t spi_cfg = {
        .role      = SPI_ROLE_SLAVE,
        .mode      = 0,   
        .bit_order = 0    
    };

    ret = spi_open(&spi_cfg);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to open SPI (%s)", esp_err_to_name(ret));
        return;
    }

    ESP_LOGI(TAG, "SPI Slave started");

    uint8_t tx_buf[SPI_MAX_BUFFER_SIZE] = "Slave - Test";
    uint8_t rx_buf[SPI_MAX_BUFFER_SIZE] = {0};

    while (1)
    {
        ESP_LOGI(TAG, "Waiting for SPI master...");

        ret = spi_transceive(tx_buf, rx_buf, sizeof(tx_buf));
        if (ret == ESP_OK)
        {
            ESP_LOGI(TAG, "RX Texto: %s", rx_buf);
        }
        else
        {
            ESP_LOGE(TAG, "SPI receive failed (%s)", esp_err_to_name(ret));
        }
    }
}