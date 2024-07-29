#include <8051.h>
/*
    LED Blink
*/
// Function prototype

#define LED_PIN P2_0

void delay(void);

void main(void) {
    while (1) {

        //LED 
        LED_PIN = 1;
        delay();         
        LED_PIN = 0;
        delay();         

    }
}

void delay(void) {
    unsigned long i;
    for (i = 0; i < 100000; i++);  // Simple delay loop
}
