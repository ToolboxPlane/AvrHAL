/**
 * @file pwm16bit.c
 * @author paul
 * @date 14.04.19
 * @brief pwm16bit @TODO
 */

#include "pwm16bit.h"

#include <avr/io.h>

void pwm1_init(pwm_clock_option_t pwm_clock_option, uint16_t top) {
    TCCR1A = 0b10101010; // Enable all three outputs in non inverting mode, set to Fast PWM with ICRn as TOP (mode 14)
    TCCR1B = 0b00011000 | pwm_clock_option; //No input capture, select the prescaler
    TCCR1C = 0x00; // No force output compare
    TIMSK1 = 0x00; // No interrupts
    TIFR1 = 0x00; // Clear all interrupt flags

    ICR1 = top; // Set the top value
    TCNT1 = 0;
}

void pwm1_set_out_a(uint16_t val) {
    OCR1A = val;
}

void pwm1_set_out_b(uint16_t val) {
    OCR1B = val;
}

void pwm1_set_out_c(uint16_t val) {
    OCR1C = val;
}
