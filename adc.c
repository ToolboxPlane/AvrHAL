//
// Created by paul on 20.01.18.
//
#include <avr/io.h>
#include "adc.h"

void adc_init(void) {
    ADCSRA = 0b10000000; // Enable, the ADC, no interrupts, prescaler 2
    ADCSRB = 0x00; // Right adjusted, data
}

uint16_t adc_read_sync(uint8_t channel) {
    ADMUX = 1 << REFS0 | channel; // Internal Ref | Select the channel
    ADCSRA |= 1 << ADSC; // Start conversion
    while(ADCSRA & (1 << ADSC)); // conversion running
    return ADCL | ADCH << 8; // Low byte must be read first
}
