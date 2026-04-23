/**
 * @file SPI_Master.h
 * @brief SPI Master driver interface for ESP-to-ESP communication.
 *
 * This driver defines the public API for a SPI Master responsible for
 * synchronous communication with another ESP acting as a SPI Slave.
 *
 * The implementation may use either hardware SPI or bit-banged GPIO,
 * depending on the .c file implementation.
 *
 * @author Pedro Henrique Elias Paz
 */

#ifndef SPI_MASTER_H
#define SPI_MASTER_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPI Master configuration structure
 */
typedef struct
{
    uint32_t clock_hz;   /**< SPI clock frequency in Hz */
    uint8_t  mode;       /**< SPI mode (0 to 3: CPOL/CPHA) */
    uint8_t  bit_order;  /**< Bit order: 0 = MSB first, 1 = LSB first */

} spi_master_config_t;

/**
 * @brief Initialize and open the SPI Master driver.
 *
 * This function configures the SPI Master and prepares it for communication
 * with a SPI Slave device.
 *
 * @param cfg Pointer to SPI Master configuration structure
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_master_open(const spi_master_config_t *cfg);

/**
 * @brief Close the SPI Master driver.
 *
 * Releases internal resources and disables SPI communication.
 *
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_master_close(void);

/**
 * @brief Perform a full-duplex SPI transaction.
 *
 * The Master generates the clock and simultaneously transmits and receives data.
 *
 * @param tx_data Pointer to transmit buffer (can be NULL to send dummy data)
 * @param rx_data Pointer to receive buffer (can be NULL to discard received data)
 * @param length  Number of bytes to transfer
 *
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_master_transceive(const uint8_t *tx_data, uint8_t *rx_data,size_t length);

/**
 * @brief Check whether the SPI Master driver is open.
 *
 * @return true if the driver is initialized and open, false otherwise
 */
bool spi_master_is_open(void);

#ifdef __cplusplus
}
#endif

#endif /* SPI_MASTER_H */