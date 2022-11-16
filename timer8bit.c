/**
 * @file timer8bit.c
 * @author paul
 * @date 14.04.19
 * @brief timer8bit @TODO
 */

#include "timer8bit.h"

#include <avr/interrupt.h>
#include <avr/io.h>

typedef struct {
    volatile timer_callback_t callback;
    volatile uint8_t *const tccra, *const tccrb, *const timsk, *const tcnt;
} timer8bit_instance_t;

static volatile timer8bit_instance_t instance = {
#if defined(__AVR_ATmega328P__)
        .tccra = &TCCR2A,
        .tccrb = &TCCR2B,
        .timsk = &TIMSK2,
        .tcnt = &TCNT2
#elif defined(__AVR_ATmega2560__)
        .tccra = &TCCR0A,
        .tccrb = &TCCR0B,
        .timsk = &TIMSK0,
        .tcnt = &TCNT0
#else
    #error "Please define a CPU, using the mmcpu flag"
#endif
};


#if defined(__AVR_ATmega328P__)
ISR(TIMER2_OVF_vect) {
#elif defined(__AVR_ATmega2560__)
ISR(TIMER0_OVF_vect) {
#endif
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
