/**
 * @file i2c.h
 * @author paul
 * @date 12.04.19
 * @brief i2c @TODO
 */

#ifndef FLIGHTCONTROLLER_I2C_H
#define FLIGHTCONTROLLER_I2C_H

#include <stdint.h>
#include <stdbool.h>

/**
 * Some shortcuts for the most used i2c frequencies.
 * @see i2c_init
 */
#define I2C_CLOCK_100K 18,1
#define I2C_CLOCK_400K 3,1

/**
 * Initialize and enable the i2c in master mode. The scl-frequency is calculated as
 * F_CPU/(16+2*twbr*4^twps). For the standard frequencies 100K and 400K there is also a
 * define above.
 * @param twbr the twi bit rate register value
 * @param twps the twi prescaler bits (only two bits, so values need to be in [0,3]
 */
void i2c_init(uint8_t twbr, uint8_t twps);
void i2c_send_receive(uint8_t addr, const uint8_t *send, uint16_t send_size,
        uint8_t *recv, uint16_t recv_size, void (*callback)(bool));


#endif //FLIGHTCONTROLLER_I2C_H
