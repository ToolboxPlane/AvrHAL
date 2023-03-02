/**
 * @file timer8bit.h
 * @author Paul Nykiel
 * @date 14.04.19
 * @brief Definition of the library functions for the 8-bit timer as software interrupt.
 * @ingroup HAL
 */

#ifndef AVR_HAL_TIMER8BIT_H
#define AVR_HAL_TIMER8BIT_H

#include <stdint.h>

/**
 * Type of the callback used for signalling a timer overflow.
 */
typedef void (*timer_8bit_callback_t)(void);

/**
 * Possible prescaler value for the 8 bit timer.
 *
 * For timer 0 the following options are invalid:
 *  * prescaler_32
 *  * prescaler_128
 *
 * For timer 2 the following options are invalid:
 *  * external_falling
 *  * external_rising
 */
typedef enum {
    no_clock,
    prescaler_1,
    prescaler_8,
    prescaler_32,
    prescaler_64,
    prescaler_128,
    prescaler_256,
    prescaler_1024,
    external_falling,
    external_rising
} timer_8bit_clock_option_t;

/**
 * ID of the 8-bit timers.
 */
typedef enum { TIMER_ID_0 = 0, TIMER_ID_2 = 1 } timer_8bit_id_t;


/**
 * @brief Initialize, enable and start the timer.
 *
 * For the initialization the following register settings are used (for the corresponding timer id):
 *  * Timer/Counter Control Register A:
 *      * Compare Match Output A/B: Disconnected (0)
 *      * Waveform Generation: Normal (0)
 *  * Timer/Counter Control Register B:
 *      * Force Output Compare A/B: disabled
 *      * Waveform Generation: See TCCA
 *      * Clock select depending on parameter "timer_clock_option"
 * * Timer/Counter: initialized to 0
 * * Timer/Counter Interrupt Mask Register: Overflow interrupt (bit 0) enabled
 *
 * @param num id of the timer
 * @param timer_clock_option the prescaler
 * @param callback a functor that gets called on every overflow
 */
void timer_8bit_init(timer_8bit_id_t num, timer_8bit_clock_option_t timer_clock_option, timer_8bit_callback_t callback);

/**
 * @brief Read the current value of the timer
 *
 * Returns the value of the Timer/Counter Register
 *
 * @param num id of the timer
 * @return a value in [0, 255] representing the value of the timer
 */
uint8_t timer_8bit_get_count(timer_8bit_id_t num);

#endif // AVR_HAL_TIMER8BIT_H
