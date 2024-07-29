#include <8051.h>

//CLOCK Params
#define FOSC 11059200UL //Frequency of Oscillator in Hz
#define TIMER_TICKS_PER_MS (FOSC/12/1000) // No.of timer ticks per millisecond

//IO Ports
#define LED_PORT P2

void delay_t0_mode1(unsigned int delay_ms){

    unsigned long ticks = delay_ms * TIMER_TICKS_PER_MS;

    TMOD &= 0xF0; // Clear the lower nibble for Timer 0
    TMOD |= 0x01; // Set the Timer 0 in Mode 1 (16bit timer)

    while(ticks > 0){
        unsigned long delay_ticks = (ticks > 65536) ? 65536 : ticks;

        //Note : This is a 16bit value.
        unsigned int delay_tick_start = 65536 - delay_ticks; 

        //Feed these values into Timer 0 register
        TH0 = delay_tick_start >> 8; //Get the higher 8bits
        TL0 = delay_tick_start & 0xFF; // Get the lower 8bits

        //Start the timer 0
        TR0 = 1;

        while(TF0 == 0); // Wait for overflow

        TR0 = 0; // Stop the Timer 0
        TF0 = 0; //Reset the overflow flag

        ticks -= delay_ticks;

    }

}

void main(){

    while(1){
        LED_PORT = 0xAA;
        delay_t0_mode1(500);
        LED_PORT = 0x55;
        delay_t0_mode1(500);
    }


}