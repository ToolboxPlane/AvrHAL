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
 *
 * @param lsb_first
 * @param f_bit refer to page 198
 */
void spi_init(bool lsb_first, uint8_t f_bit);

void spi_tx_rx(uint8_t *buf, uint16_t size);


#endif //FLIGHTCONTROLLER_SPI_H
