#include <8051.h>

#define FOSC 11059200UL // "Frequency of the Oscillator in Hz."
#define TIMER_TICKS_PER_MS (FOSC/12/1000)// Number of timer ticks per millisecond

#define LED_RED P2_0
#define LED_GREEN P2_3
#define LED_BLUE P2_7

void soft_delay(void);
void timer0_delay(unsigned int delay_ms);

int main(void){

    while(1){

        LED_RED = 1;
        LED_GREEN = 0;
        LED_BLUE = 0;
        timer0_delay(500);

        LED_RED = 0;
        LED_GREEN = 1;
        LED_BLUE = 0;
        timer0_delay(500);

        LED_RED = 0;
        LED_GREEN = 0;
        LED_BLUE = 1;
        timer0_delay(500);

    }

}

void soft_delay(void){
    unsigned int i;
    for(i=0;i<50000;i++);
}

void timer0_delay(unsigned int delay_ms){

    unsigned long ticks = delay_ms * TIMER_TICKS_PER_MS;

    TMOD &= 0xF0; //Clear the lower nibble for Timer 0
    TMOD |= 0x01; //Set the Timer0 to Mode 1 (16-Bit timer)

    while(ticks > 0){
        unsigned long delay_ticks = (ticks > 65536) ? 65536 : ticks;

        unsigned int delay_tick_start = 65536 - delay_ticks;
        TH0 = delay_tick_start >> 8;
        TL0 = delay_tick_start & 0xFF;

        TR0 = 1; //Start the Timer 0 

        while(TF0 == 0); // Wait for overflow

        TR0 = 0; //Stop the Timer0
        TF0 = 0; //Clear the overflow flag

        ticks -= delay_ticks;
    }
}