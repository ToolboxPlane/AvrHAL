/**
 * @file i2c.c
 * @author paul
 * @date 12.04.19
 * @brief i2c @TODO
 */

#include "i2c.h"

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t _addr = 0;
volatile const uint8_t *_send = 0;
volatile uint16_t _send_size = 0;
volatile uint8_t *_recv = 0;
volatile uint16_t _recv_size = 0;
void (*_callback)(bool) = 0;
volatile bool _restart_sent = false;

ISR(TWI_vect) {
    uint8_t status = TWSR & 0b11111000;

    if (_send_size > 0) {
        if (status == 0x08) { // Start transmitted, transmit the address
            TWDR = (_addr << 1) | 0; // Load the adress with the write bit
            TWCR = 0b10000101; // Start the transmission by clearing the interrupt flag
        } else if (status == 0x18 || status == 0x28) { // Address or Data transmitted, ACK received
            TWDR = *_send++;
            --_send_size;
            TWCR = 0b10000101;// Start the transmission by clearing the interrupt flag
        } else {
            // No ACK received, repeated start successful (we shouldn't be here),
            // Arbitration lost (we have only one master, this should not happen)
            (*_callback)(false);
        }
    } else if (_recv_size > 0) {
        if (!_restart_sent) { // Need to send the repeated start
            TWCR = 0b10100101; // Generate the start condition
            _restart_sent = true;
        } else {
            if (status == 0x08 || status == 0x10) { // (Re)start send, write the adress
                TWDR = (_addr << 1) | 1; // Load the adress with the write bit
                TWCR = 0b10000101; // Start the transmission by clearing the interrupt flag
            } else if (status == 0x40 || status == 0x50) { // Address/Data send, ack received
                *_recv++ = TWDR;
                --_recv_size;
                TWCR = 0b11000101; // Generate an ACK
            } else if (status == 0x58) { // Data byte received, NACK received
                *_recv++ = TWDR;
                --_recv_size;
                TWCR = 0b10000101; // Generate an NACK
                (*_callback)(true);
            } else {
                // Arbitration lost in SLA+R or NACK bit
                (*_callback)(false);
            }
        }
    } else {
        (*_callback)(true);
    }
}

void i2c_init(uint8_t twbr, uint8_t twps) {
    TWBR = twbr;
    TWSR = twps & 0b11;
}

void i2c_send_receive(uint8_t addr, const uint8_t *send, uint16_t send_size, uint8_t *recv, uint16_t recv_size,
                      void (*callback)(bool)) {
    _addr = addr & 0b1111111;
    _send = send;
    _send_size = send_size;
    _recv = recv;
    _recv_size = recv_size;
    _callback = callback;
    _restart_sent = false;

    TWCR = 0b10100101; // Generate the start condition
}
