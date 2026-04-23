/**
 * @file SPI_Slave.h
 * @brief SPI Slave driver interface for ESP-to-ESP communication.
 *
 * This driver defines the public API for a SPI Slave device used to
 * communicate synchronously with a SPI Master running on another ESP.
 *
 * The Slave does not generate the clock and only responds to transactions
 * initiated by the Master.
 *
 * @author Pedro Henrique Elias Paz
 */

#ifndef SPI_SLAVE_H
#define SPI_SLAVE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPI Slave configuration structure
 */
typedef struct
{
    uint8_t mode;        /**< SPI mode (0 to 3: CPOL/CPHA) */
    uint8_t bit_order;   /**< Bit order: 0 = MSB first, 1 = LSB first */

} spi_slave_config_t;

/**
 * @brief Initialize and open the SPI Slave driver.
 *
 * Prepares the Slave to receive clock and data from a SPI Master.
 *
 * @param cfg Pointer to Slave configuration structure
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_slave_open(const spi_slave_config_t *cfg);

/**
 * @brief Close the SPI Slave driver.
 *
 * Disables SPI Slave operation and releases internal resources.
 *
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_slave_close(void);

/**
 * @brief Perform a full-duplex SPI transaction as a Slave.
 *
 * This function blocks until the Master initiates a SPI transaction.
 * Data is received and transmitted simultaneously.
 *
 * @param tx_data Pointer to transmit buffer (can be NULL to send dummy data)
 * @param rx_data Pointer to receive buffer (can be NULL to discard received data)
 * @param length  Number of bytes to transfer
 *
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_slave_transceive(const uint8_t *tx_data, uint8_t *rx_data, size_t length);

/**
 * @brief Check whether the SPI Slave driver is open.
 *
 * @return true if the driver is initialized and open, false otherwise
 */
bool spi_slave_is_open(void);

#ifdef __cplusplus
}
#endif

#endif /* SPI_SLAVE_H */