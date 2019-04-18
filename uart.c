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

typedef struct {
    volatile uart_callback_t callback;
    volatile uint8_t data[RING_BUFFER_SIZE];
    // Nomenclature: Data is written into the buf at head and read at tail
    volatile uint8_t tail;
    volatile uint8_t head;
    volatile bool full;
    volatile bool ready;
    volatile uint8_t * const ucsra, * const ucsrb, * const ucsrc;
    volatile uint16_t * const ubrr;
    volatile uint8_t * const udr;
} uart_instance_t;

uart_instance_t instances[4] = {
    {.ucsra = &UCSR0A, .ucsrb = &UCSR0B, .ucsrc = &UCSR0C, .ubrr = &UBRR0, .udr = &UDR0},
    {.ucsra = &UCSR1A, .ucsrb = &UCSR1B, .ucsrc = &UCSR1C, .ubrr = &UBRR1, .udr = &UDR1},
    {.ucsra = &UCSR2A, .ucsrb = &UCSR2B, .ucsrc = &UCSR2C, .ubrr = &UBRR2, .udr = &UDR2},
    {.ucsra = &UCSR3A, .ucsrb = &UCSR3B, .ucsrc = &UCSR3C, .ubrr = &UBRR3, .udr = &UDR3}
};

// Data register empty
void udre_handler(uint8_t id) {
    if (instances[id].full ||
            instances[id].head != instances[id].tail) { // Still data available
        *instances[id].udr = instances[id].data[instances[id].tail];
        instances[id].tail = (instances[id].tail + 1) % RING_BUFFER_SIZE;
        instances[id].full = false;
    } else {
        instances[id].ready = true;
    }
}

// New byte
void rx_handler(uint8_t id) {
    if(instances[id].callback) {
        (*instances[id].callback)(*instances[id].udr);
    }
}

ISR(USART0_UDRE_vect) { udre_handler(0); }
ISR(USART1_UDRE_vect) { udre_handler(1); }
ISR(USART2_UDRE_vect) { udre_handler(2); }
ISR(USART3_UDRE_vect) { udre_handler(3); }
ISR(USART0_RX_vect) { rx_handler(0); }
ISR(USART1_RX_vect) { rx_handler(1); }
ISR(USART2_RX_vect) { rx_handler(2); }
ISR(USART3_RX_vect) { rx_handler(3); }

void uart_init(uint8_t id, uint32_t baud, uart_callback_t rx_callback) {
    instances[id].callback = rx_callback;
    instances[id].tail = 0;
    instances[id].head = 0;
    instances[id].full = false;
    instances[id].ready = true;
    *instances[id].ucsra = 0b00000000; // Reset all flags, no double transmission speed
    *instances[id].ucsrb = 0b10111000; // RX complete isr, data register empty isr, rx, tx enabled, 8 bit data
    *instances[id].ucsrc = 0b00000110; // Async UART, No Parity, 1 Stop Bit, 8 data bits
    *instances[id].ubrr = F_CPU / (16 * baud) - 1;
}

void uart_send_byte(uint8_t id, uint8_t data) {
    if (instances[id].ready) { // Can send directly
        instances[id].ready = false;
        *instances[id].udr = data;
    } else if (instances[id].tail != instances[id].head
                || !instances[id].full) { // Not empty but needs to be added to queue
        instances[id].data[instances[id].head] = data;
        instances[id].head = (instances[id].head + 1) % RING_BUFFER_SIZE;
        if (instances[id].tail == instances[id].head) {
            instances[id].full = true;
        }
    } else { // Queue full
        while (instances[id].full);
        instances[id].data[instances[id].head] = data;
        instances[id].head = (instances[id].head + 1) % RING_BUFFER_SIZE;
        if (instances[id].tail == instances[id].head) {
            instances[id].full = true;
        }
    }
}

void uart_send_buf(uint8_t id, const uint8_t *data, uint16_t size) {
    for (uint16_t c = 0; c < size; c++) {
        uart_send_byte(id, data[c]);
    }
}
