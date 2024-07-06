#include <8051.h>

#define SWITCH_PIN P2_0
#define GREENLED_PIN P2_1
#define REDLED_PIN P2_2

void delay(void);
void main(void)
{
    //Set the input pin to high
    SWITCH_PIN = 1;

    while (1)
    {

        //Check if the button is pressed or not
        if(SWITCH_PIN == 0)
        {
            GREENLED_PIN = 1;
            REDLED_PIN = 0;
            
        }
        else{

            GREENLED_PIN = 0;
            REDLED_PIN = 1;

        }

    }
}

void delay(void)
{
    unsigned long i;

    for (i = 0; i < 100000; i++);
}