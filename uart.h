/**
 * @file uart.h
 * @author paul
 * @date 12.04.19
 * @brief Definition of the library functions for the universal-asynchronous-receiver-transmitter module.
 */

#include <stdint.h>

#ifndef AVR_HAL_UART_H
#define AVR_HAL_UART_H

typedef void (*uart_callback_t)(uint8_t);

typedef enum { NONE = 0b00, EVEN = 0b10, ODD = 0b11 } uart_parity_t;

/**
 * Initialize and enable the uart 0
 * @param uart_id the number of the uart should be in [0,3]
 * @param baud the baud-rate (for example 9600)
 * @param parity the type of parity to use
 * @param stop_bits the number of stop bits to use, needs to be in [1, 2]
 * @param rx_callback a functor which gets called everytime there is a new byte
 */
void uart_init(uint8_t uart_id, uint32_t baud, uart_parity_t parity, uint8_t stop_bits, uart_callback_t rx_callback);

/**
 * Send a single byte via the uart. This function manages an ring buffer (with size 32), to
 * buffer the data befor sending. If this ring buffer is full this functions blocks until a byte
 * had been sent.
 * @param uart_id the number of the uart should be in [0,3]
 * @param data the byte to send
 */
void uart_send_byte(uint8_t uart_id, uint8_t data);

/**
 * Sends multiple bytes via the uart.
 * @see uart_send_byte for more information about the blocking behaviour of this function.
 * @param data a pointer to the first element to send
 * @param size the number of elements to send
 */
void uart_send_buf(uint8_t uart_id, const uint8_t *data, uint16_t size);

#endif // AVR_HAL_UART_H
