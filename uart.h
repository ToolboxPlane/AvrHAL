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

void uart0_init(uint32_t baud, uart_callback_t rx_callback);

#endif //FLIGHTCONTROLLER_UART_H
