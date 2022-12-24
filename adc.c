/**
 * @file adc.c
 * @author Paul Nykiel
 * @date 20.01.18.
 * @brief Implementation of the library functions for the analog digital converter.
 * @ingroup HAL
 */

#include "adc.h"

#include <avr/io.h>

void adc_init(void) {
    ADCSRA = 0b10000111; // Enable, the ADC, no interrupts, Prescaler 128
    ADCSRB = 0x00;       // Right adjusted, data
}

uint16_t adc_read_sync(uint8_t channel) {
    ADMUX = 0b01U << 6 | channel; // Internal Ref | Select the channel
    ADCSRA |= 1U << ADSC;         // Start conversion
    while (ADCSRA & (1U << ADSC))
        ;                       // conversion running
    return ADCL | (ADCH << 8u); // Low byte must be read first
}
