/**
 * @file spi.c
 * @author paul
 * @date 12.04.19
 * @brief spi @TODO
 */

#include "spi.h"

#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint8_t *_buf = 0;
static volatile uint16_t _size = 0;
static void (*_callback)(void) = 0;

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
    SPCR |= prescaler & 0b11;
    SPSR = (prescaler >> 2u) & 0b1;

#if defined(__AVR_ATmega328P__)
    DDRB |= (1 << 3u) | (1 << 5u); // MOSI and SCK as Output
#endif
}

void spi_tx_rx(uint8_t *buf, uint16_t size, void (*callback)(void)) {
    _buf = buf;
    _size = size;
    _callback = callback;
    if (_size > 0) {
        SPDR = *_buf;
        --_size;
    }
}
