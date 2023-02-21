make_test(MODULE_UNDER_TEST ../pwm16bit.c
        TEST_DEFINITION pwm16bit.cpp
        REQUIRED_HEADERS
            ${MockLib_SOURCE_DIR}/../System/avr/io.h)
make_test(MODULE_UNDER_TEST ../timer8bit.c
        TEST_DEFINITION timer8bit.cpp
        REQUIRED_HEADERS
            ${MockLib_SOURCE_DIR}/../System/avr/io.h)
make_test(MODULE_UNDER_TEST ../uart.c
        TEST_DEFINITION uart.cpp
        REQUIRED_HEADERS
            ${MockLib_SOURCE_DIR}/../System/avr/io.h)
