/**
 * @file uart.c
 * @author paul
 * @date 12.04.19
 * @brief uart @TODO
 */

#include "uart.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uart_callback_t uart0_callback = 0;

// uart0 data register empty, lets send new data
ISR(USART0_UDRE_vect) {
}

ISR(USART0_RX_vect) {
    if (uart0_callback) {
        (*uart0_callback)(UDR0);
    }
}

void uart0_init(uint32_t baud, uart_callback_t rx_callback) {
    uart0_callback = rx_callback;
    UCSR0A = 0b00000000; // Reset all flags, no double transmission speed
    UCSR0B = 0b10111000; // RX complete isr, data register empty isr, rx, tx enabled, 8 bit data
    UCSR0C = 0b00000110; // Async UART, No Parity, 1 Stop Bit, 8 data bits
    UBRR0  = F_CPU / (16 * baud) - 1;
}

