/**
 * @file pwm16bit.c
 * @author Paul Nykiel
 * @date 14.04.19
 * @brief Implementation of the library functions for the pulse width modulation using the 16bit timer.
 */

#include "pwm16bit.h"

#include <avr/io.h>

typedef struct {
    volatile uint8_t *const tccra, *const tccrb, *const tccrc, *const timsk, *const tifr;
    volatile uint16_t *const icr, *const tcnt;
    volatile uint16_t *const ocra, *const ocrb, *const ocrc;
} pwm_instance_t;


static pwm_instance_t instances[] = {{0},
                                     {.tccra = &TCCR1A,
                                      .tccrb = &TCCR1B,
                                      .tccrc = &TCCR1C,
                                      .timsk = &TIMSK1,
                                      .tifr = &TIFR1,
                                      .icr = &ICR1,
                                      .tcnt = &TCNT1,
                                      .ocra = &OCR1A,
                                      .ocrb = &OCR1B,
                                      .ocrc = &OCR1C},
                                     {0},
                                     {.tccra = &TCCR3A,
                                      .tccrb = &TCCR3B,
                                      .tccrc = &TCCR3C,
                                      .timsk = &TIMSK3,
                                      .tifr = &TIFR3,
                                      .icr = &ICR3,
                                      .tcnt = &TCNT3,
                                      .ocra = &OCR3A,
                                      .ocrb = &OCR3B,
                                      .ocrc = &OCR3C},
                                     {.tccra = &TCCR4A,
                                      .tccrb = &TCCR4B,
                                      .tccrc = &TCCR4C,
                                      .timsk = &TIMSK4,
                                      .tifr = &TIFR4,
                                      .icr = &ICR4,
                                      .tcnt = &TCNT4,
                                      .ocra = &OCR4A,
                                      .ocrb = &OCR4B,
                                      .ocrc = &OCR4C},
                                     {.tccra = &TCCR5A,
                                      .tccrb = &TCCR5B,
                                      .tccrc = &TCCR5C,
                                      .timsk = &TIMSK5,
                                      .tifr = &TIFR5,
                                      .icr = &ICR5,
                                      .tcnt = &TCNT5,
                                      .ocra = &OCR5A,
                                      .ocrb = &OCR5B,
                                      .ocrc = &OCR5C}};

void pwm_init(uint8_t timer_id, pwm_clock_option_t pwm_clock_option, uint16_t top) {
    *instances[timer_id].tccra =
            0b10101010u; // Enable all three outputs in non inverting mode, set to Fast PWM with ICRn as TOP (mode 14)
    *instances[timer_id].tccrb = 0b00011000u | pwm_clock_option; // No input capture, select the prescaler
    *instances[timer_id].tccrc = 0x00u;                          // No force output compare
    *instances[timer_id].timsk = 0x00u;                          // No interrupts
    *instances[timer_id].tifr = 0x00u;                           // Clear all interrupt flags
    *instances[timer_id].icr = top;                              // Set the top value
    *instances[timer_id].tcnt = 0u;
}

void pwm_set_out_a(uint8_t timer_id, uint16_t val) {
    *instances[timer_id].ocra = val;
}

void pwm_set_out_b(uint8_t timer_id, uint16_t val) {
    *instances[timer_id].ocrb = val;
}

void pwm_set_out_c(uint8_t timer_id, uint16_t val) {
    *instances[timer_id].ocrc = val;
}
