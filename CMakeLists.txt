project(AvrHAL)
add_library(${PROJECT_NAME} STATIC adc.c i2c.c pwm16bit.c spi.c timer8bit.c uart.c)

add_subdirectory(External/MockTools)
add_subdirectory(Tests)
