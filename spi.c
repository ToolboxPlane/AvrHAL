/**
 * @file spi.c
 * @author Paul Nykiel
 * @date 12.04.19
 * @brief Implementation of the library functions for the serial peripheral interface.
 * @ingroup HAL
 */

#include "spi.h"

#include <avr/interrupt.h>
#include <avr/io.h>

static volatile uint8_t *_buf = 0;
static volatile uint16_t _size = 0;
static spi_callback_t _callback = 0;

ISR(SPI_STC_vect) {
    *_buf = SPDR;
    ++_buf;
    if (_size > 0) {
        SPDR = *_buf;
        --_size;
    } else {
        if (_callback != 0) {
            (*_callback)();
        }
    }
}

void spi_init(bool lsb_first, spi_prescaler_t prescaler) {
    SPCR = 0b11010000; // Enabled, Interrupts enabled, Slave mode
    if (lsb_first) {
        SPCR |= (1 << DORD);
    }
    SPCR |= prescaler & 0b11u;
    SPSR = (prescaler >> 2u) & 0b1u;
}

void spi_tx_rx(uint8_t *buf, uint16_t size, spi_callback_t callback) {
    _buf = buf;
    _size = size;
    _callback = callback;
    if (_size > 0) {
        SPDR = *_buf;
        --_size;
    }
}
