//
// Created by paul on 20.01.18.
//

#ifndef AVR_HAL_ADC_H
#define AVR_HAL_ADC_H

#include <stdint.h>

/**
 * Initialize the adc to use in synchronous (blocking) mode
 */
void adc_init(void);

/**
 * Read a single channel (blocking)
 * @param channel the channel, needs to be in [0,7]
 * @return the analogue 10bit measurement (value in [0,1023])
 */
uint16_t adc_read_sync(uint8_t channel);

#endif // AVR_HAL_ADC_H
