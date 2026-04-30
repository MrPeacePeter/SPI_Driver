/**
 * @file SPI_Drv.c
 * @brief Generic SPI driver implementation (Master or Slave) for ESP-IDF.
 *
 * This implementation supports a single SPI instance that can operate
 * either as Master or Slave depending on runtime configuration.
 *
 * Author: Pedro Henrique Elias Paz
 */

#include "SPI_Drv.h"

#include <string.h>

#include "driver/spi_master.h"
#include "driver/spi_slave.h"
#include "driver/gpio.h"
#include "esp_log.h"

/* =========================================================================
 * Definitions
 * ========================================================================= */

static const char *TAG = "SPI";

#define SPI_MOSI_PIN 39
#define SPI_MISO_PIN 36
#define SPI_SCLK_PIN 37
#define SPI_CS_PIN   35

#define SPI_HOST_USED SPI2_HOST

/* =========================================================================
 * Internal state
 * ========================================================================= */

static bool           s_is_open = false;
static spi_role_t     s_role    = SPI_ROLE_MASTER;
static spi_device_handle_t s_master_dev;

/* =========================================================================
 * Public API implementation
 * ========================================================================= */

esp_err_t spi_open(const spi_config_t *cfg)
{
    esp_err_t ret;

    if (cfg == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }

    if (s_is_open)
    {
        return ESP_ERR_INVALID_STATE;
    }

    if (cfg->mode > 3)
    {
        return ESP_ERR_INVALID_ARG;
    }

    s_role = cfg->role;

    /* ===================== MASTER ===================== */
    if (cfg->role == SPI_ROLE_MASTER)
    {
        if (cfg->clock_hz == 0)
        {
            return ESP_ERR_INVALID_ARG;
        }

        spi_bus_config_t buscfg = {
            .mosi_io_num = SPI_MOSI_PIN,
            .miso_io_num = SPI_MISO_PIN,
            .sclk_io_num = SPI_SCLK_PIN,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1,
            .max_transfer_sz = 4096
        };

        spi_device_interface_config_t devcfg = {
            .clock_speed_hz = cfg->clock_hz,
            .mode = cfg->mode,
            .spics_io_num = SPI_CS_PIN,
            .queue_size = 1,
            .flags = (cfg->bit_order == 1) ? SPI_DEVICE_TXBIT_LSBFIRST | SPI_DEVICE_RXBIT_LSBFIRST : 0
        };

        ret = spi_bus_initialize(SPI_HOST_USED, &buscfg, SPI_DMA_CH_AUTO);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "spi_bus_initialize failed");
            return ret;
        }

        ret = spi_bus_add_device(SPI_HOST_USED, &devcfg, &s_master_dev);
        if (ret != ESP_OK)
        {
            spi_bus_free(SPI_HOST_USED);
            ESP_LOGE(TAG, "spi_bus_add_device failed");
            return ret;
        }

        ESP_LOGI(TAG, "SPI initialized as MASTER");
    }

    /* ===================== SLAVE ===================== */
    else
    {
        spi_bus_config_t buscfg = {
            .mosi_io_num = SPI_MOSI_PIN,
            .miso_io_num = SPI_MISO_PIN,
            .sclk_io_num = SPI_SCLK_PIN,
            .quadwp_io_num = -1,
            .quadhd_io_num = -1
        };

        spi_slave_interface_config_t slvcfg = {
            .mode = cfg->mode,
            .spics_io_num = SPI_CS_PIN,
            .queue_size = 1,
            .flags = (cfg->bit_order == 1) ? SPI_SLAVE_TXBIT_LSBFIRST | SPI_SLAVE_RXBIT_LSBFIRST : 0
        };

        ret = spi_slave_initialize(SPI_HOST_USED, &buscfg, &slvcfg, SPI_DMA_CH_AUTO);
        if (ret != ESP_OK)
        {
            ESP_LOGE(TAG, "spi_slave_initialize failed");
            return ret;
        }

        ESP_LOGI(TAG, "SPI initialized as SLAVE");
    }

    s_is_open = true;
    return ESP_OK;
}

esp_err_t spi_close(void)
{
    if (!s_is_open)
    {
        return ESP_ERR_INVALID_STATE;
    }

    if (s_role == SPI_ROLE_MASTER)
    {
        spi_bus_remove_device(s_master_dev);
        spi_bus_free(SPI_HOST_USED);
    }
    else
    {
        spi_slave_free(SPI_HOST_USED);
    }

    s_is_open = false;
    return ESP_OK;
}

esp_err_t spi_transceive(const uint8_t *tx_data,
                         uint8_t *rx_data,
                         size_t length)
{
    if (!s_is_open || length == 0)
    {
        return ESP_ERR_INVALID_STATE;
    }

    if (s_role == SPI_ROLE_MASTER)
    {
        spi_transaction_t t;
        memset(&t, 0, sizeof(t));

        t.length    = length * 8;
        t.tx_buffer = tx_data;
        t.rx_buffer = rx_data;

        return spi_device_transmit(s_master_dev, &t);
    }
    else
    {
        spi_slave_transaction_t t;
        memset(&t, 0, sizeof(t));

        t.length    = length * 8;
        t.tx_buffer = tx_data;
        t.rx_buffer = rx_data;

        return spi_slave_transmit(SPI_HOST_USED, &t, portMAX_DELAY);
    }
}

bool spi_is_open(void)
{
    return s_is_open;
}

spi_role_t spi_get_role(void)
{
    return s_role;
}