#include <gtest/gtest.h>
#include <Mock/io.hpp>

extern "C" {
#include <HAL/pwm16bit.h>
}

TEST(TEST_NAME, init_timer_1_basic) {
    /*
     * Initialize timer 1 with no_clock (=0) as clock option and top=0
     */
    pwm_init(1, no_clock, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}

TEST(TEST_NAME, init_timer_3_basic) {
    /*
     * Initialize timer 3 with no_clock (=0) as clock option and top=0
     */
    pwm_init(3, no_clock, 0);

    EXPECT_EQ((TCCR3A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR3A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR3A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR3A & 0b11U) | ((TCCR3B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR3B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR3B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR3B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR3B & 0b111U, 0); // Clock Select
    EXPECT_EQ((TCCR3C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR3C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR3C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT3, 0); // Timer/Counter
    EXPECT_EQ(OCR3A, 0); // Output compare register A
    EXPECT_EQ(OCR3B, 0); // Output compare register B
    EXPECT_EQ(OCR3C, 0); // Output compare register C
    EXPECT_EQ(ICR3, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK3 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK3 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK3 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK3 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK3 >> 0U) & 0b1U, 0); // TOIEn
}

TEST(TEST_NAME, init_timer_4_basic) {
    /*
     * Initialize timer 4 with no_clock (=0) as clock option and top=0
     */
    pwm_init(4, no_clock, 0);

    EXPECT_EQ((TCCR4A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR4A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR4A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR4A & 0b11U) | ((TCCR4B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR4B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR4B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR4B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR4B & 0b111U, 0); // Clock Select
    EXPECT_EQ((TCCR4C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR4C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR4C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT4, 0); // Timer/Counter
    EXPECT_EQ(OCR4A, 0); // Output compare register A
    EXPECT_EQ(OCR4B, 0); // Output compare register B
    EXPECT_EQ(OCR4C, 0); // Output compare register C
    EXPECT_EQ(ICR4, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK4 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK4 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK4 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK4 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK4 >> 0U) & 0b1U, 0); // TOIEn
}

TEST(TEST_NAME, init_timer_5_basic) {
    /*
     * Initialize timer 5 with no_clock (=0) as clock option and top=0
     */
    pwm_init(5, no_clock, 0);

    EXPECT_EQ((TCCR5A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR5A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR5A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR5A & 0b11U) | ((TCCR5B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR5B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR5B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR5B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR5B & 0b111U, 0); // Clock Select
    EXPECT_EQ((TCCR5C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR5C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR5C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT5, 0); // Timer/Counter
    EXPECT_EQ(OCR5A, 0); // Output compare register A
    EXPECT_EQ(OCR5B, 0); // Output compare register B
    EXPECT_EQ(OCR5C, 0); // Output compare register C
    EXPECT_EQ(ICR5, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK5 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK5 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK5 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK5 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK5 >> 0U) & 0b1U, 0); // TOIEn
}

TEST(TEST_NAME, init_timer_prescaler_1) {
    /*
     * Initialize timer 1 with prescaler 1 as clock option and top=0
     */
    pwm_init(1, prescaler_1, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0b001); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}

TEST(TEST_NAME, init_timer_prescaler_8) {
    /*
     * Initialize timer 1 with prescaler 8 as clock option and top=0
     */
    pwm_init(1, prescaler_8, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0b010); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}

TEST(TEST_NAME, init_timer_prescaler_64) {
    /*
     * Initialize timer 1 with prescaler 64 as clock option and top=0
     */
    pwm_init(1, prescaler_64, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0b011); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}

TEST(TEST_NAME, init_timer_prescaler_256) {
    /*
     * Initialize timer 1 with prescaler 256 as clock option and top=0
     */
    pwm_init(1, prescaler_256, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0b100); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}
TEST(TEST_NAME, init_timer_prescaler_1024) {
    /*
     * Initialize timer 1 with prescaler 1024 as clock option and top=0
     */
    pwm_init(1, prescaler_1024, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0b101); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}
TEST(TEST_NAME, init_timer_clock_falling) {
    /*
     * Initialize timer 1 with external falling as clock option and top=0
     */
    pwm_init(1, external_falling, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0b110); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}
TEST(TEST_NAME, init_timer_clock_rising) {
    /*
     * Initialize timer 1 with external rising as clock option and top=0
     */
    pwm_init(1, external_rising, 0);

    EXPECT_EQ((TCCR1A >> 6U) & 0b11U, 2); // COMnA
    EXPECT_EQ((TCCR1A >> 4U) & 0b11U, 2); // COMnB
    EXPECT_EQ((TCCR1A >> 2U) & 0b11U, 2); // COMnC
    EXPECT_EQ((TCCR1A & 0b11U) | ((TCCR1B >> 1U) & 0b1100U), 14); // WGMn
    EXPECT_EQ((TCCR1B >> 7U) & 0b1U, 0); // ICNC
    EXPECT_EQ((TCCR1B >> 6U) & 0b1U, 0); // ICES
    EXPECT_EQ((TCCR1B >> 5U) & 0b1U, 0); // Reserved
    EXPECT_EQ(TCCR1B & 0b111U, 0b111); // Clock Select
    EXPECT_EQ((TCCR1C >> 7U) & 0b1, 0); // Force Output Compare A
    EXPECT_EQ((TCCR1C >> 6U) & 0b1, 0); // Force Output Compare B
    EXPECT_EQ((TCCR1C >> 5U) & 0b1, 0); // Force Output Compare C
    EXPECT_EQ(TCNT1, 0); // Timer/Counter
    EXPECT_EQ(OCR1A, 0); // Output compare register A
    EXPECT_EQ(OCR1B, 0); // Output compare register B
    EXPECT_EQ(OCR1C, 0); // Output compare register C
    EXPECT_EQ(ICR1, 0); // Input Capture register (i.e. top)
    EXPECT_EQ((TIMSK1 >> 5U) & 0b1U, 0); // ICIE
    EXPECT_EQ((TIMSK1 >> 3U) & 0b1U, 0); // OICIEnC
    EXPECT_EQ((TIMSK1 >> 2U) & 0b1U, 0); // OICIEnB
    EXPECT_EQ((TIMSK1 >> 1U) & 0b1U, 0); // OICIEnA
    EXPECT_EQ((TIMSK1 >> 0U) & 0b1U, 0); // TOIEn
}
