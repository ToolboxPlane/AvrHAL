/**
 * @file uart.h
 * @author paul
 * @date 12.04.19
 * @brief uart @TODO
 */

#include <stdint.h>

#ifndef FLIGHTCONTROLLER_UART_H
#define FLIGHTCONTROLLER_UART_H

typedef void (*uart_callback_t)(uint8_t);

/**
 * Initialize and enable the uart 0
 * @param baud the baud-rate (for example 9600)
 * @param rx_callback a functor which gets called everytime there is a new byte
 */
void uart0_init(uint32_t baud, uart_callback_t rx_callback);

/**
 * Send a single byte via the uart. This function manages an ring buffer (with size 32), to
 * buffer the data befor sending. If this ring buffer is full this functions blocks until a byte
 * had been sent.
 * @param data the byte to send
 */
void uart0_send_byte(uint8_t data);

/**
 * Sends multiple bytes via the uart.
 * @see uart0_send_byte for more information about the blocking behaviour of this function.
 * @param data a pointer to the first element to send
 * @param size the number of elements to send
 */
void uart0_send_buf(const uint8_t *data, uint16_t size);

#endif //FLIGHTCONTROLLER_UART_H
