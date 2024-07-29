#include <8051.h>

#define FOSC 11059200UL
#define TIMER_TICKS_PER_MS (FOSC/12/1000)

#define LED_PIN P2_0
#define BUTTON_1 P2_6
#define BUTTON_2 P2_7

void delay_timer0_mode1(unsigned int delay_ms){
    unsigned int total_delay_ticks = delay_ms * TIMER_TICKS_PER_MS;

    //Set the Timer 0 to mode 1
    TMOD &= 0xF0; // Clear the lower nibble for Timer 0
    TMOD |= 0x01; //Set Timer 0 to Mode 1 (16-bit timer)

    while(total_delay_ticks > 0){

        unsigned delay_ticks_part = total_delay_ticks > 65536 ? 65536 : total_delay_ticks;
        unsigned delay_ticks_start = 65536 - total_delay_ticks;

        TH0 = delay_ticks_start >> 8;
        TL0 = delay_ticks_start & 0x0F;

        TR0 = 1; //Start the Timer0
        while(TF0 == 0);

        TR0 = 0; // Stop the Timer0
        TF0 = 0; //Reset the overflow flag

        total_delay_ticks -= delay_ticks_part;

    }

}

void main(void){

    LED_PIN = 0; //Turn off LED initially

    //Set the buttons to high since P2 has internal pull-up resistor. 
    //So when button is pressed, the logic 0 is set.
    BUTTON_1 = 1; 
    BUTTON_2 = 1;

    while(1){
        
        if(BUTTON_1 == 0 && BUTTON_2 == 0)
        {
            LED_PIN = 1;
        }
        else
        {
            LED_PIN = 0;
        }

    }
}