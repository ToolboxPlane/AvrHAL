/**
 * @file timer8bit.h
 * @author paul
 * @date 14.04.19
 * @brief timer8bit @TODO
 */

#ifndef AVR_HAL_TIMER8BIT_H
#define AVR_HAL_TIMER8BIT_H

typedef void (*timer_callback_t)(void);

#include <avr/io.h>

typedef enum {
#if defined(__AVR_ATmega328P__)
    no_clock = 0,
    prescaler_1 = 1,
    prescaler_8 = 2,
    prescaler_32 = 3,
    prescaler_64 = 4,
    prescaler_128 = 5,
    prescaler_256 = 6,
    prescaler_1024 = 7
#elif defined (__AVR_ATmega2560__)
    no_clock = 0,
    prescaler_1 = 1,
    prescaler_8 = 2,
    prescaler_64 = 3,
    prescaler_256 = 4,
    prescaler_1024 = 5,
    external_falling = 6,
    external_rising = 7
#endif
} timer_clock_option_t;


/**
 * Initialize, enable and start the timer.
 * @param timer_clock_option the prescaler
 * @param callback a functor that gets called on every overflow
 */
void timer_8bit_init(timer_clock_option_t timer_clock_option, timer_callback_t callback);

#endif //AVR_HAL_TIMER8BIT_H
