#include <8051.h>

//#define FOSC 12000000UL // 12 MHz oscillator frequency
#define FOSC 11059200UL // 11.0592 MHz oscillator frequency
#define TIMER_TICKS_PER_MS (FOSC / 12 / 1000) // Number of timer ticks per millisecond

#define LED_PIN P2_0
#define DELAY_MS 100

void delay_ms(unsigned int ms);

void main(void) {
    while(1) {
        LED_PIN = 1;
        delay_ms(DELAY_MS);
        LED_PIN = 0;
        delay_ms(DELAY_MS);
    }
}

void delay_ms(unsigned int ms) {
    unsigned long ticks = ms * TIMER_TICKS_PER_MS;
    
    TMOD &= 0xF0; // Clear lower nibble for Timer0
    TMOD |= 0x01; // Set Timer-0 to Mode 1 (16-bit timer)

    while (ticks > 0) {
        unsigned long delay_ticks = (ticks > 65536) ? 65536 : ticks;

        TH0 = (65536 - delay_ticks) >> 8; // Calculate the initial values for the timer
        TL0 = (65536 - delay_ticks) & 0xFF;

        TR0 = 1; // Start the timer
        while (TF0 == 0); // Wait for overflow
        TR0 = 0; // Stop the timer
        TF0 = 0; // Clear overflow flag

        ticks -= delay_ticks;
    }
}
