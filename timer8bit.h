/**
 * @file timer8bit.h
 * @author Paul Nykiel
 * @date 14.04.19
 * @brief Definition of the library functions for the 8-bit timer as software interrupt.
 */

#ifndef AVR_HAL_TIMER8BIT_H
#define AVR_HAL_TIMER8BIT_H

#include <stdint.h>

/**
 * Type of the callback used for signalling a timer overflow.
 */
typedef void (*timer_callback_t)(void);

/**
 * Possible prescaler value for the 8 bit timer.
 */
typedef enum {
    no_clock = 0,
    prescaler_1 = 1,
    prescaler_8 = 2,
    prescaler_64 = 3,
    prescaler_256 = 4,
    prescaler_1024 = 5,
    external_falling = 6,
    external_rising = 7
} timer_clock_option_t;


/**
 * Initialize, enable and start the timer.
 * @param timer_clock_option the prescaler
 * @param callback a functor that gets called on every overflow
 */
void timer_8bit_init(timer_clock_option_t timer_clock_option, timer_callback_t callback);

/**
 * Read the current value of the timer
 * @return a value in [0, 255] representing the value of the timer
 */
uint8_t timer_8bit_get_count(void);

#endif // AVR_HAL_TIMER8BIT_H
