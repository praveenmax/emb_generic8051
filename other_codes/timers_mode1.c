#include <8051.h>

#define LED_PIN P2_1
#define FULL_OVERFLOW_COUNT 7 //For 500ms delay

void delay_500_ms(void);

void main(void){
    while(1){
        LED_PIN = 1;
        delay_500_ms();
        LED_PIN = 0;
        delay_500_ms();

    }
}

void delay_500_ms(void)
{
    TMOD |= 0x01; // Set Timer-0 to Mode 1 (16-bit timer)

    // Handle 7 full overflows
    // Timer setup for full overflow counts from 0 to 65535
    TH0 = 0x00;  // Load high byte of timer count for full overflow
    TL0 = 0x00;  // Load low byte of timer count

    for(unsigned char i = 0; i < FULL_OVERFLOW_COUNT ; i++){
        TR0 = 1; //Start the Timer
        while(TF0 == 0); //Wait until Timer-0 overflow flag is set
        TR0 = 2; //Stop the timer
        TF0 = 0; //Clear Timer-0 overflow flag

    }

    //Handle the remaining 2077 (0xF6B3) cycles

    TH0 = 0xF6;
    TL0 = 0xB3;

    TR0 = 1;    

    while(TF0 == 0);
    TR0 = 0;
    TF0 = 0;
}
