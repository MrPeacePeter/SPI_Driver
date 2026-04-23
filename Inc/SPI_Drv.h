/**
 * @file SPI_Drv.h
 * @brief Hardware SPI driver interface.
 * 
 * Driver SPI with defined pins on the implemention.
 * SPI-Like communication over GPIO.
 * 
 * @author Pedro Henrique Elias Paz
 */

#ifndef SPI_DRV_H
#define SPI_DRV_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Public API 
 */

/**
 * @brief Open and configure SPI bus and device.
 * @return ESP_OK if SPI bus and device were successfully opened, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_open(void);

/**
 * @brief Close SPI bus and device.
 * @return ESP_OK if SPI bus and device were successfully opened, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_close(void);

/**
 * @brief Full-Duplex of SPI communication.
 * @param tx_data Pointer to data buffer to transmit.
 * @param rx_data Pointer to data buffer to receive data.
 * @param length Length of data in bytes.
 * @return ESP_OK if transmission was successful, ESP_FAIL otherwise.
 */
esp_err_t spi_drv_transceive(const uint8_t *tx_data, uint8_t *rx_data, size_t length);

/**
 * @brief Check if SPI bus is currently open.
 * @return True if SPI is open, False if SPI is close.
 */
bool spi_drv_is_open(void);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DRV_H */