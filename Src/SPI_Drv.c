/**
 * @file SPI_Drv.h
 * @brief Hardware SPI driver implementation.
 * @author Pedro Henrique Elias Paz
 */
 
#include "driver/spi_master.h"
#include "esp_log.h"
#include "driver/gpio.h" 
#include "SPI_Drv.h"

#define SPI_PIN_MOSI 39
#define SPI_PIN_MISO 36
#define SPI_PIN_SLCK 37
#define SPI_PIN_CS 35
#define SPI_MODE 0
#define TAG SPI_Drv "SPI_DRIVER"

esp_err_t spi_drv_open (void){
    
}