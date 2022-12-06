/**
 * @file i2c.h
 * @author Paul Nykiel
 * @date 12.04.19
 * @brief Definition of the library functions for the inter-integrated-circuit module.
 */

#ifndef AVR_HAL_I2C_H
#define AVR_HAL_I2C_H

#include <stdbool.h>
#include <stdint.h>

/**
 * Some shortcuts for the most used i2c frequencies.
 * @see i2c_init
 */
#define I2C_CLOCK_100K 18, 1
#define I2C_CLOCK_400K 3, 1

/**
 * Initialize and enable the i2c in master mode. The scl-frequency is calculated as
 * F_CPU/(16+2*twbr*4^twps). For the standard frequencies 100K and 400K there is also a
 * define above.
 * @param twbr the twi bit rate register value
 * @param twps the twi prescaler bits (only two bits, so values need to be in [0,3]
 */
void i2c_init(uint8_t twbr, uint8_t twps);

/**
 * Send a buffer to a device and then read a number of bytes from the device.
 * @param addr the 7-bit adress of the device (without the RW-Bit)
 * @param send a pointer to the data to send
 * @param send_size the number of bytes to send
 * @param recv a pointer to the location where the received bytes should be written to (can be the same as send)
 * @param recv_size the number of bytes to read
 * @param callback a function that gets called after the transmission, the bool signals if everything was successful
 */
void i2c_send_receive(uint8_t addr, const uint8_t *send, uint16_t send_size, uint8_t *recv, uint16_t recv_size,
                      void (*callback)(bool));


#endif // AVR_HAL_I2C_H
