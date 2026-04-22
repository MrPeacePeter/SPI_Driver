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
 * Public API 
 */

/**
 * @brief Open and configure SPI bus and device.
 * @param cfg Pointer to SPI configuration structure.
 * @return ESP_OK if SPI bus and device were successfully opened, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_open(void);

/**
 * @brief Close SPI bus and device.
 */
esp_err_t spi_drv_close(void);

/**
 * @brief Transmit data over SPI - Full Duplex.
 * @param tx_data Pointer to data buffer to transmit.
 * @param length Length of data in bytes.
 * @return ESP_OK if transmission was successful, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_transmit(const uint8_t *tx_data, size_t length);

/**
 * @brief Transmit data over SPI - Full Duplex.
 * @param rx_data Pointer to data buffer to receive data.
 * @return ESP_OK if transmission was successful, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_receiver(uint8_t *rx_data); 

/**
 * @brief Check if SPI bus is currently open.
 */
void spi_drv_is_open(void);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DRV_H */