/**
 * @file timer8bit.c
 * @author paul
 * @date 14.04.19
 * @brief timer8bit @TODO
 */

#include "timer8bit.h"

#include <avr/io.h>
#include <avr/interrupt.h>

static void (*_callback)(void);

ISR(TIMER0_OVF_vect) {
    if (_callback != 0) {
        (*_callback)();
    }
}

void timer0_init(timer_clock_option_t timer_clock_option, void (*callback)(void)) {
    _callback = callback;
    TCCR0A = 0b00000000u; // Output compare disconnected, normal mode
    TCCR0B = 0b00000000u | timer_clock_option; // No force override, normal mode, prescaler
    TIMSK0 = 0b00000001u; // Overflow interrupt enabled

    TCNT0 = 0; // Set the counter to 0
}
