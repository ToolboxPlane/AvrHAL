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
 * @brief Initialize, enable and start the pwm
 *
 * For the initialization the following register settings are used (for the corresponding timer id):
 *  * Timer/Counter Control Register A:
 *      * Waveform Generation: Fast PWM with ICRn as top (mode 14), see Table 17.2
 *      * Compare Output mode: non inverting mode (mode 2), see Table 17.4
 *  * Timer/Counter Control Register B:
 *      * Input Capture Noise Canceller: disabled, as no input is captured
 *      * Input Capture Edge Select: disabled, as no input is captured
 *      * Waveform Generation: see TCCA
 *      * Clock Select: according to parameter pwm_clock_option
 * * Timer/Counter Control Register C:
 *      * Force Output compare: disabled as PWM is active
 * * Timer/Counter: initialized to 0
 * * Output Compare Registers: initialized to 0
 * * Input Capture Registers: defines the top in PWM mode, set to parameter "top"
 * * Timer/Counter Interrupt Mask Register: All interrupt disabled
 * * Timer/Counter Interrupt Flag Registers: not applicable as interrupts are disabled
 *
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param pwm_clock_option a value of pwm_clock_option_t to select the prescaler
 * @param top the maximum value of the counter, should be in [1,65535]
 */
void pwm_init(uint8_t timer_id, pwm_clock_option_t pwm_clock_option, uint16_t top);

/**
 * @brief Set the PWM output a (OCnA) to specific duty cycle (relative to top)
 *
 * To set the duty cycle the parameter "val" is written to the respective Output Compare Register A
 *
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param val the compare value, the duty cycle is given by val/top
 */
void pwm_set_out_a(uint8_t timer_id, uint16_t val);

/**
 * @brief Set the PWM output b (OCnB) to specific duty cycle (relative to top)
 *
 * To set the duty cycle the parameter "val" is written to the respective Output Compare Register B
 *
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param val the compare value, the duty cycle is given by val/top
 */
void pwm_set_out_b(uint8_t timer_id, uint16_t val);

/**
 * @brief Set the PWM output c (OCnC) to specific duty cycle (relative to top)
 *
 * To set the duty cycle the parameter "val" is written to the respective Output Compare Register C
 *
 * @param timer_id the number of the timer, should be in {1,3,4,5}
 * @param val the compare value, the duty cycle is given by val/top
 */
void pwm_set_out_c(uint8_t timer_id, uint16_t val);

#endif // AVR_HAL_PWM16BIT_H
