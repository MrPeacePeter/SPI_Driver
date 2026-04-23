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
#define SPI_CLK 1000000
#define SPI_QUEUE 1

#define TAG "SPI_DRIVER"

spi_device_handle_t handle;


esp_err_t spi_drv_open (void){
    
    ESP_LOGI(TAG, "Opening SPI peripheral");

    spi_bus_config_t spi_config = {
        .mosi_io_num = SPI_PIN_MOSI,
        .miso_io_num = SPI_PIN_MISO,
        .sclk_io_num = SPI_PIN_SLCK
    };

    spi_device_interface_config_t spi_device_config = {
        .clock_source = SPI_CLK,
        .mode = SPI_MODE,
        .queue_size = SPI_QUEUE
    };

    if(spi_bus_initialize(SPI2_HOST, &spi_config, SPI_DMA_CH_AUTO) != ESP_OK){
        return ESP_FAIL;
    }

    if(spi_bus_add_device(SPI2_HOST, &spi_device_config, &handle) != ESP_OK){
        return ESP_FAIL;
    }

    ESP_LOGI(TAG, "SPI peripheral opened successfully");
    return ESP_OK;
}

/*esp_err_t spi_drv_transceive(const uint8_t *tx_data, uint8_t *rx_data, size_t length){
    ESP_LOGI(TAG, "SPI Transmiting");
    
    spi_transaction_t t;

    //snprintf(*tx_data, sizeof(*tx_data), );


}*/