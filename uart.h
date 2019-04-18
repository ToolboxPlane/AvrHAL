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
 * @param id the number of the uart should be in [0,3]
 * @param baud the baud-rate (for example 9600)
 * @param rx_callback a functor which gets called everytime there is a new byte
 */
void uart_init(uint8_t id, uint32_t baud, uart_callback_t rx_callback);

/**
 * Send a single byte via the uart. This function manages an ring buffer (with size 32), to
 * buffer the data befor sending. If this ring buffer is full this functions blocks until a byte
 * had been sent.
 * @param id the number of the uart should be in [0,3]
 * @param data the byte to send
 */
void uart_send_byte(uint8_t id, uint8_t data);

/**
 * Sends multiple bytes via the uart.
 * @see uart_send_byte for more information about the blocking behaviour of this function.
 * @param data a pointer to the first element to send
 * @param size the number of elements to send
 */
void uart_send_buf(uint8_t id, const uint8_t *data, uint16_t size);

#endif //FLIGHTCONTROLLER_UART_H
