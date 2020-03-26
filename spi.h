/**
 * @file spi.h
 * @author paul
 * @date 12.04.19
 * @brief spi @TODO
 */

#ifndef AVR_HAL_SPI_H
#define AVR_HAL_SPI_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    DIV_2 = 0b100,
    DIV_4 = 0b000,
    DIV_8 = 0b101,
    DIV_16 = 0b001,
    DIV_32 = 0b110,
    DIV_64 = 0b010,
    DIV_64_2X = 0b111,
    DIV_128 = 0b011
} spi_prescaler_t;

/**
 * Initialize and enable the spi in master mode.
 * @param lsb_first true if the data should be send (and received) with the least significant bit first
 * @param prescaler the 3 bits responsible for selecting the prescaler (refer to page 198 for more information)
 */
void spi_init(bool lsb_first, spi_prescaler_t prescaler);

/**
 * Send and receive a number of bytes via the interface. The buffer is used for reading the data to send
 * but is also used to write the data which got read.
 * @param buf the input-output buffer
 * @param size the number of elements to read/write
 * @param callback a functor that gets called when the transmission is complete
 */
void spi_tx_rx(uint8_t *buf, uint16_t size, void (*callback)(void));


#endif //AVR_HAL_SPI_H
