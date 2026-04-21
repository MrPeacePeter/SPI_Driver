/**
 * @file SPI_Drv.h
 * @brief Hardware SPI driver interface.
 * @author Pedro Henrique Elias Paz
 */

#ifndef SPI_DRV_H
#define SPI_DRV_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Public Types
 */

typedef struct 
{
    spi_host_device_t host;
    gpio_num_t mosi_pin;
    gpio_num_t miso_pin;
    gpio_num_t sclk_pin;
    gpio_num_t cs_pin;
    spi_mode_t mode;

    uint32_t clock_speed_hz;
} spi_drv_cfg_t;

/**
 * Public API 
    */

/**
 * @brief Open and configure SPI bus and device.
 * @param cfg Pointer to SPI configuration structure.
 * @return ESP_OK if SPI bus and device were successfully opened, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_open(const spi_drv_cfg_t *cfg);

/**
 * @brief Close SPI bus and device.
 */
esp_err_t spi_drv_close(void);

/**
 * @brief Transmit data over SPI - Full Duplex.
 * @param tx_data Pointer to data buffer to transmit.
 * @param rx_data Pointer to data buffer to receive data.
 * @param length Length of data in bytes.
 * @return ESP_OK if transmission was successful, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_transmit(const uint8_t *tx_data, uint8_t *rx_data, size_t length);

/**
 * @brief Check if SPI bus is currently open.
 */
void spi_drv_is_open(void);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DRV_H */