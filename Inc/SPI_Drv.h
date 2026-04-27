/**
 * @file SPI.h
 * @brief Generic SPI driver interface (Master or Slave) for ESP-to-ESP communication.
 *
 * This driver provides a unified SPI API that can operate either as
 * a Master or a Slave, depending on the configuration passed during initialization.
 *
 * @author Pedro Henrique Elias Paz
 */

#ifndef SPI_H
#define SPI_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief SPI device role
 */
typedef enum
{
    SPI_ROLE_MASTER = 0,
    SPI_ROLE_SLAVE
} spi_role_t;

/**
 * @brief SPI configuration structure
 */
typedef struct
{
    spi_role_t role;     /**< Master or Slave */

    uint8_t mode;        /**< SPI mode (0–3: CPOL/CPHA) */
    uint8_t bit_order;   /**< 0 = MSB first, 1 = LSB first */

    /* Master-only parameters */
    uint32_t clock_hz;   /**< SPI clock frequency (only for Master) */

} spi_config_t;

/**
 * @brief Initialize and open the SPI driver.
 *
 * Configures the SPI peripheral as Master or Slave.
 *
 * @param cfg Pointer to SPI configuration structure
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_open(const spi_config_t *cfg);

/**
 * @brief Close the SPI driver.
 *
 * Disables SPI operation and releases internal resources.
 *
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_close(void);

/**
 * @brief Perform a full-duplex SPI transaction.
 *
 * - Master: initiates the transaction and generates the clock.
 * - Slave: blocks until the Master initiates a transaction.
 *
 * @param tx_data Pointer to transmit buffer (NULL to send dummy data)
 * @param rx_data Pointer to receive buffer (NULL to discard received data)
 * @param length  Number of bytes to transfer
 *
 * @return ESP_OK on success, error code otherwise
 */
esp_err_t spi_transceive(const uint8_t *tx_data,
                         uint8_t *rx_data,
                         size_t length);

/**
 * @brief Check whether the SPI driver is open.
 *
 * @return true if the driver is initialized and open, false otherwise
 */
bool spi_is_open(void);

/**
 * @brief Get current SPI role.
 *
 * @return SPI_ROLE_MASTER or SPI_ROLE_SLAVE
 */
spi_role_t spi_get_role(void);

#ifdef __cplusplus
}
#endif

#endif /* SPI_H */