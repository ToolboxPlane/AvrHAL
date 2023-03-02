#include <gtest/gtest.h>
#include <Mock/io.hpp>

extern "C" {
#include <HAL/timer8bit.h>
#include <System/avr/interrupt.h>
}

bool callbackCalled = false;
void callback() {
    callbackCalled = true;
}


TEST(TEST_NAME, init__timer_0_no_clock) {
    timer_8bit_init(TIMER_ID_0, no_clock, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 0); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_prescaler_1) {
    timer_8bit_init(TIMER_ID_0, prescaler_1, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 1); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_prescaler_8) {
    timer_8bit_init(TIMER_ID_0, prescaler_8, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 2); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_prescaler_64) {
    timer_8bit_init(TIMER_ID_0, prescaler_64, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 3); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_prescaler_256) {
    timer_8bit_init(TIMER_ID_0, prescaler_256, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 4); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_prescaler_1024) {
    timer_8bit_init(TIMER_ID_0, prescaler_1024, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 5); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_prescaler_clock_falling) {
    timer_8bit_init(TIMER_ID_0, external_falling, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 6); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_prescaler_clock_rising) {
    timer_8bit_init(TIMER_ID_0, external_rising, nullptr);

    EXPECT_EQ((TCCR0A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR0A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR0B >> 1U) & (0b100U)) | (TCCR0A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR0B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR0B & 0b111U), 7); // CS
    EXPECT_EQ(TCNT0, 0);
    EXPECT_EQ(TIMSK0, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_0_callback) {
    timer_8bit_init(TIMER_ID_0, no_clock, callback);
    callbackCalled = false;
    TIMER0_OVF_vect();
    EXPECT_TRUE(callbackCalled);
}

TEST(TEST_NAME, init__timer_2_no_clock) {
    timer_8bit_init(TIMER_ID_2, no_clock, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 0); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_prescaler_1) {
    timer_8bit_init(TIMER_ID_2, prescaler_1, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 1); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_prescaler_8) {
    timer_8bit_init(TIMER_ID_2, prescaler_8, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 2); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_prescaler_32) {
    timer_8bit_init(TIMER_ID_2, prescaler_32, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 3); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_prescaler_64) {
    timer_8bit_init(TIMER_ID_2, prescaler_64, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 4); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_prescaler_128) {
    timer_8bit_init(TIMER_ID_2, prescaler_128, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 5); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_prescaler_256) {
    timer_8bit_init(TIMER_ID_2, prescaler_256, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 6); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_prescaler_1024) {
    timer_8bit_init(TIMER_ID_2, prescaler_1024, nullptr);

    EXPECT_EQ((TCCR2A >> 6U) & 0b11U, 0); //COMnA
    EXPECT_EQ((TCCR2A >> 4U) & 0b11U, 0); //COMnB
    EXPECT_EQ(((TCCR2B >> 1U) & (0b100U)) | (TCCR2A & 0b11U), 0); // WGMn
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnA
    EXPECT_EQ((TCCR2B >> 7U) & 0b1U, 0); //FOCnB
    EXPECT_EQ((TCCR2B & 0b111U), 7); // CS
    EXPECT_EQ(TCNT2, 0);
    EXPECT_EQ(TIMSK2, 0b00000001); // Interrupts: only OV
}

TEST(TEST_NAME, init__timer_2_callback) {
    timer_8bit_init(TIMER_ID_2, no_clock, callback);
    callbackCalled = false;
    TIMER2_OVF_vect();
    EXPECT_TRUE(callbackCalled);
}

TEST(TEST_NAME, get__timer_0_0) {
    TCNT0 = 0;
    EXPECT_EQ(timer_8bit_get_count(TIMER_ID_0), 0);
}

TEST(TEST_NAME, get__timer_0_17) {
    TCNT0 = 17;
    EXPECT_EQ(timer_8bit_get_count(TIMER_ID_0), 17);
}

TEST(TEST_NAME, get__timer_0_255) {
    TCNT0 = 255;
    EXPECT_EQ(timer_8bit_get_count(TIMER_ID_0), 255);
}

TEST(TEST_NAME, get__timer_2_0) {
    TCNT2 = 0;
    EXPECT_EQ(timer_8bit_get_count(TIMER_ID_2), 0);
}

TEST(TEST_NAME, get__timer_2_17) {
    TCNT2 = 17;
    EXPECT_EQ(timer_8bit_get_count(TIMER_ID_2), 17);
}

TEST(TEST_NAME, get__timer_2_255) {
    TCNT2 = 255;
    EXPECT_EQ(timer_8bit_get_count(TIMER_ID_2), 255);
}
