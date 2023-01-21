/**
 * @file timer8bit.c
 * @author Paul Nykiel
 * @date 14.04.19
 * @brief Implementation of the library functions for the 8-bit timer as software interrupt.
 * @ingroup HAL
 */

#include "timer8bit.h"

#include <avr/interrupt.h>
#include <avr/io.h>

typedef struct {
    volatile timer_8bit_callback_t callback;
    volatile uint8_t *const tccra, *const tccrb, *const timsk, *const tcnt;
} timer8bit_instance_t;

static volatile timer8bit_instance_t instances[] = {
        {.tccra = &TCCR0A, .tccrb = &TCCR0B, .timsk = &TIMSK0, .tcnt = &TCNT0},
        {.tccra = &TCCR2A, .tccrb = &TCCR2B, .timsk = &TIMSK2, .tcnt = &TCNT2}};

const static uint8_t prescaler_bits[2][10] = {
        /*Timer 0:*/
        {/*no_clock=*/0,
         /*prescaler_1=*/1,
         /*prescaler_8=*/2,
         /*prescaler_32=*/0,
         /*prescaler_64=*/3,
         /*prescaler_128=*/0,
         /*prescaler_256=*/4,
         /*prescaler_1024=*/5,
         /*external_falling*/ 6,
         /*external_rising=*/7},

        /* Timer 1: */
        {/*no_clock=*/0,
         /*prescaler_1=*/1,
         /*prescaler_8=*/2,
         /*prescaler_32=*/3,
         /*prescaler_64=*/4,
         /*prescaler_128=*/5,
         /*prescaler_256=*/6,
         /*prescaler_1024=*/7,
         /*external_falling*/ 0,
         /*external_rising=*/0},
};


ISR(TIMER0_OVF_vect) {
    if (instances[TIMER_ID_0].callback != 0) {
        (*instances[TIMER_ID_0].callback)();
    }
}

ISR(TIMER2_OVF_vect) {
    if (instances[TIMER_ID_2].callback != 0) {
        (*instances[TIMER_ID_2].callback)();
    }
}

void timer_8bit_init(timer_id_t num, timer_8bit_clock_option_t timer_clock_option, timer_8bit_callback_t callback) {
    instances[num].callback = callback;
    *instances[num].tccra = 0b00000000u; // Output compare disconnected, normal mode
    *instances[num].tccrb =
            0b00000000u | prescaler_bits[num][timer_clock_option]; // No force override, normal mode, prescaler
    *instances[num].timsk = 0b00000001u;                           // Overflow interrupt enabled

    *instances[num].tcnt = 0; // Set the counter to 0
}

uint8_t timer_8bit_get_count(timer_id_t num) {
    return *instances[num].tcnt;
}
