/**
 * @file timer8bit.c
 * @author paul
 * @date 14.04.19
 * @brief Implementation of the library functions for the 8-bit timer as software interrupt.
 */

#include "timer8bit.h"

#include <avr/interrupt.h>
#include <avr/io.h>

typedef struct {
    volatile timer_callback_t callback;
    volatile uint8_t *const tccra, *const tccrb, *const timsk, *const tcnt;
} timer8bit_instance_t;

static volatile timer8bit_instance_t instance = {.tccra = &TCCR0A, .tccrb = &TCCR0B, .timsk = &TIMSK0, .tcnt = &TCNT0};


ISR(TIMER0_OVF_vect) {
    if (instance.callback != 0) {
        (*instance.callback)();
    }
}

void timer_8bit_init(timer_clock_option_t timer_clock_option, timer_callback_t callback) {
    instance.callback = callback;
    *instance.tccra = 0b00000000u;                      // Output compare disconnected, normal mode
    *instance.tccrb = 0b00000000u | timer_clock_option; // No force override, normal mode, prescaler
    *instance.timsk = 0b00000001u;                      // Overflow interrupt enabled

    *instance.tcnt = 0; // Set the counter to 0
}

uint8_t timer_8bit_get_count() {
    return *instance.tcnt;
}
