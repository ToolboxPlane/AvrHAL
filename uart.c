/**
 * @file uart.c
 * @author paul
 * @date 12.04.19
 * @brief uart @TODO
 */

#include "uart.h"

#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#define RING_BUFFER_SIZE 32

volatile uart_callback_t uart0_callback = 0;
// Nomenclature: Data is written into the buf at head and read at tail
volatile uint8_t uart0_data[RING_BUFFER_SIZE];
volatile uint8_t uart0_tail = 0;
volatile uint8_t uart0_head = 0;
volatile bool uart0_full = false;
volatile bool uart0_ready = true;

// uart0 data register empty, lets send new data
ISR(USART0_UDRE_vect) {
    if (uart0_full || uart0_head != uart0_tail) { // Still data available
        UDR0 = uart0_data[uart0_tail];
        uart0_tail = (uart0_tail + 1) % RING_BUFFER_SIZE;
        uart0_full = false;
    } else {
        uart0_ready = true;
    }
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

void uart0_send_byte(uint8_t data) {
    if (uart0_ready) { // Can send directly
        uart0_ready = false;
        UDR0 = data;
    } else if (uart0_tail != uart0_head || !uart0_full) { // Not empty but needs to be added to queue
        uart0_data[uart0_head] = data;
        uart0_head = (uart0_head + 1) % RING_BUFFER_SIZE;
        if (uart0_tail == uart0_head) {
            uart0_full = true;
        }
    } else { // Queue full
        while (uart0_full);
        uart0_data[uart0_head] = data;
        uart0_head = (uart0_head + 1) % RING_BUFFER_SIZE;
        if (uart0_tail == uart0_head) {
            uart0_full = true;
        }
    }
}

void uart0_send_buf(uint8_t *data, uint16_t size) {
    for (uint16_t c = 0; c < size; c++) {
        uart0_send_byte(data[c]);
    }
}

