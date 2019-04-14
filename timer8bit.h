/**
 * @file timer8bit.h
 * @author paul
 * @date 14.04.19
 * @brief timer8bit @TODO
 */

#ifndef FLIGHTCONTROLLER_TIMER8BIT_H
#define FLIGHTCONTROLLER_TIMER8BIT_H

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

void timer0_init(timer_clock_option_t timer_clock_option, void (*callback)(void));

#endif //FLIGHTCONTROLLER_TIMER8BIT_H
