/**
 * @file pwm16bit.h
 * @author Paul Nykiel
 * @date 14.04.19
 * @brief Definition of the library functions for the pulse width modulation using the 16bit timer.
 * @ingroup HAL
 */

#ifndef AVR_HAL_PWM16BIT_H
#define AVR_HAL_PWM16BIT_H

#include <stdint.h>

/**
 * Possible prescaler options for the 16 bit timer.
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
} pwm_clock_option_t;

/**
 * Initialize, enable and start the pwm
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param pwm_clock_option a value of pwm_clock_option_t to select the prescaler
 * @param top the maximum value of the counter, should be in [1,65535]
 */
void pwm_init(uint8_t timer_id, pwm_clock_option_t pwm_clock_option, uint16_t top);

/**
 * Set the pwm1 output a to specifiy duty cycle (relative to top)
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param val the compare value, the duty cycle is given by val/top
 */
void pwm_set_out_a(uint8_t timer_id, uint16_t val);

/**
 * Set the pwm1 output b to specifiy duty cycle (relative to top)
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param val the compare value, the duty cycle is given by val/top
 */
void pwm_set_out_b(uint8_t timer_id, uint16_t val);

/**
 * Set the pwm1 output c to specifiy duty cycle (relative to top)
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param val the compare value, the duty cycle is given by val/top
 */
void pwm_set_out_c(uint8_t timer_id, uint16_t val);

#endif // AVR_HAL_PWM16BIT_H
