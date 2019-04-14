/**
 * @file spi.h
 * @author paul
 * @date 12.04.19
 * @brief spi @TODO
 */

#ifndef FLIGHTCONTROLLER_SPI_H
#define FLIGHTCONTROLLER_SPI_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Initialize and enable the spi in master mode.
 * @param lsb_first true if the data should be send (and received) with the least significant bit first
 * @param f_bit the 3 bits responsible for selecting the prescaler (refer to page 198 for more information)
 */
void spi_init(bool lsb_first, uint8_t f_bit);

/**
 * Send and receive a number of bytes via the interface. The buffer is used for reading the data to send
 * but is also used to write the data which got read.
 * @param buf the input-output buffer
 * @param size the number of elements to read/write
 * @param callback a functor that gets called when the transmission is complete
 */
void spi_tx_rx(uint8_t *buf, uint16_t size, void (*callback)(void));


#endif //FLIGHTCONTROLLER_SPI_H
