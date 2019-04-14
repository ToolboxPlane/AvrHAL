/**
 * @file pwm16bit.h
 * @author paul
 * @date 14.04.19
 * @brief pwm16bit @TODO
 */

#ifndef FLIGHTCONTROLLER_PWM16BIT_H
#define FLIGHTCONTROLLER_PWM16BIT_H

#include <stdint.h>

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

void pwm1_init(pwm_clock_option_t pwm_clock_option, uint16_t top);
void pwm1_set_out_a(uint16_t val);
void pwm1_set_out_b(uint16_t val);
void pwm1_set_out_c(uint16_t val);

#endif //FLIGHTCONTROLLER_PWM16BIT_H
