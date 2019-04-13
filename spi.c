/**
 * @file spi.c
 * @author paul
 * @date 12.04.19
 * @brief spi @TODO
 */

#include "spi.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t *_buf;
volatile uint16_t _size;

ISR(SPI_STC_vect) {
    _buf[-1] = SPDR;
    if (_size > 0) {
        SPDR = *_buf++;
        --_size;
    }
}

void spi_init(bool lsb_first, uint8_t f_bit) {
    SPCR = 0b11010000; // Enabled, Interrupts enabled, Slave mode
    if (lsb_first) {
        SPCR |= (1 << DORD);
    }
    SPCR |= f_bit & 0b11;
    SPSR = (f_bit >> 2) & 0b1;
}

void spi_tx_rx(uint8_t *buf, uint16_t size) {
    _buf = buf;
    _size = size;
    if (_size > 0) {
        SPDR = *_buf++;
        --_size;
    }
}
