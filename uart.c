/**
 * @file uart.c
 * @author paul
 * @date 12.04.19
 * @brief Implementation of the library functions for the universal-asynchronous-receiver-transmitter module.
 */

#include "uart.h"

#include <avr/interrupt.h>
#include <avr/io.h>
#include <math.h>
#include <stdbool.h>

#ifndef RING_BUFFER_SIZE
    #define RING_BUFFER_SIZE 512
#endif

#define MIN_U2X_BAUD (F_CPU / (16 * (255 + 1)) + 1)

typedef struct {
    volatile uart_callback_t callback;
    volatile uint8_t data[RING_BUFFER_SIZE];
    // Nomenclature: Data is written into the buf at head and read at tail
    volatile uint8_t tail;
    volatile uint8_t head;
    volatile bool full;
    volatile bool ready;
    volatile uint8_t *const ucsra, *const ucsrb, *const ucsrc;
    volatile uint16_t *const ubrr;
    volatile uint8_t *const udr;
} uart_instance_t;

static volatile uart_instance_t instances[] = {
        {.ucsra = &UCSR0A, .ucsrb = &UCSR0B, .ucsrc = &UCSR0C, .ubrr = &UBRR0, .udr = &UDR0},
        {.ucsra = &UCSR1A, .ucsrb = &UCSR1B, .ucsrc = &UCSR1C, .ubrr = &UBRR1, .udr = &UDR1},
        {.ucsra = &UCSR2A, .ucsrb = &UCSR2B, .ucsrc = &UCSR2C, .ubrr = &UBRR2, .udr = &UDR2},
        {.ucsra = &UCSR3A, .ucsrb = &UCSR3B, .ucsrc = &UCSR3C, .ubrr = &UBRR3, .udr = &UDR3},
};

// Data register empty
void tx_handler(uint8_t uart_id) {
    if (instances[uart_id].full || instances[uart_id].head != instances[uart_id].tail) { // Still data available
        *instances[uart_id].udr = instances[uart_id].data[instances[uart_id].tail];
        instances[uart_id].tail = (instances[uart_id].tail + 1) % RING_BUFFER_SIZE;
        instances[uart_id].full = false;
    } else {
        instances[uart_id].ready = true;
    }
}

// New byte
void rx_handler(uint8_t uart_id) {
    if (instances[uart_id].callback) {
        (*instances[uart_id].callback)(*instances[uart_id].udr);
    }
}

ISR(USART0_RX_vect) {
    rx_handler(0);
}

ISR(USART0_TX_vect) {
    tx_handler(0);
}

ISR(USART1_RX_vect) {
    rx_handler(1);
}

ISR(USART1_TX_vect) {
    tx_handler(1);
}

ISR(USART2_RX_vect) {
    rx_handler(2);
}

ISR(USART2_TX_vect) {
    tx_handler(2);
}

ISR(USART3_RX_vect) {
    rx_handler(3);
}

ISR(USART3_TX_vect) {
    tx_handler(3);
}

void uart_init(uint8_t uart_id, uint32_t baud, uart_parity_t parity, uint8_t stop_bits, uart_callback_t rx_callback) {
    instances[uart_id].callback = rx_callback;
    instances[uart_id].tail = 0;
    instances[uart_id].head = 0;
    instances[uart_id].full = false;
    instances[uart_id].ready = true;
    *instances[uart_id].ucsra = 0b00000000;              // Reset all flags, no double transmission speed
    *instances[uart_id].ucsrb = 0b11011000;              // RX complete isr, TX complete isr, rx, tx enabled, 8 bit data
    *instances[uart_id].ucsrc = 0b00000110;              // Async UART, No Parity, 1 Stop Bit, 8 data bits
    *instances[uart_id].ucsrc |= (uint8_t) parity << 4u; // Set parity to actual value
    if (stop_bits == 2) {
        *instances[uart_id].ucsrc |= 1u << 3u; // Set stop bits to two if required
    }
    if (baud > MIN_U2X_BAUD) {
        *instances[uart_id].ubrr = lroundf(F_CPU / (8.0 * baud) - 1);
        *instances[uart_id].ucsra |= (1u << 1u); // Switch to double transmission speed
    } else {
        *instances[uart_id].ubrr = lroundf(F_CPU / (16.0 * baud) - 1);
    }
}

void uart_send_byte(uint8_t uart_id, uint8_t data) {
    if (instances[uart_id].ready) { // Can send directly
        instances[uart_id].ready = false;
        *instances[uart_id].udr = data;
    } else if (instances[uart_id].tail != instances[uart_id].head ||
               !instances[uart_id].full) { // Not empty but needs to be added to queue
        instances[uart_id].data[instances[uart_id].head] = data;
        instances[uart_id].head = (instances[uart_id].head + 1) % RING_BUFFER_SIZE;
        if (instances[uart_id].tail == instances[uart_id].head) {
            instances[uart_id].full = true;
        }
    } else { // Queue full
        while (instances[uart_id].full)
            ;
        instances[uart_id].data[instances[uart_id].head] = data;
        instances[uart_id].head = (instances[uart_id].head + 1) % RING_BUFFER_SIZE;
        if (instances[uart_id].tail == instances[uart_id].head) {
            instances[uart_id].full = true;
        }
    }
}

void uart_send_buf(uint8_t uart_id, const uint8_t *data, uint16_t size) {
    for (uint16_t c = 0; c < size; c++) {
        uart_send_byte(uart_id, data[c]);
    }
}
