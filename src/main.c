#include <8051.h>
/*
    Traffic signal demo

*/
// Function prototype
void delay(void);

void main(void) {
    while (1) {
        //RED LED 
        P2 |= (1 << 0);  //SET to HIGH
        P2 &= ~( (1 << 3) | (1 << 7) ); //SET these PINS to LOW
        delay();         
        delay();         
        P2 &= ~(1 << 0); 

        //YELLOW LED
        P2 |= 1 << 3;
        P2 &= ~((1<<0) | (1<<7));
        delay();
        P2 &= ~(1 << 3);     
        
        //GREEN LED
        P2 |= (1 << 7);
        P2 &= ~((1<<0) | (1<<3));
        delay();
        delay();
        P2 &= ~(1 << 7);

        delay();
        P2 |= (1<<0) | (1<<3) | (1<<7);
        delay();
        delay();
        delay();

    }
}

void delay(void) {
    unsigned long i;
    for (i = 0; i < 100000; i++);  // Simple delay loop
}
