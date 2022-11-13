project(AvrHAL)
add_library(${PROJECT_NAME} STATIC adc.c i2c.c pwm16bit.c spi.c timer8bit.c)
target_include_directories(${PROJECT_NAME} INTERFACE .)
