#include <8051.h>

//Clock stuffs
#define FOSC 11059200UL
#define TICKS_PER_MS (FOSC/12/1000)

//LCD Stuffs
#define RS_PIN P2_0
#define RW_PIN P2_1
#define EN_PIN P2_2
#define LCD_DATA_BUS P3

//Misc
#define LED_PIN P2_3

void delay_timer0_mode1(unsigned int delay_ms){

    unsigned long total_delay_ticks = delay_ms * TICKS_PER_MS;

    //Set T0 in mode 1
    TMOD &= 0xF0;
    TMOD |= 0x01;

    while(total_delay_ticks > 0){
        unsigned int delay_ticks_part = total_delay_ticks > 65535 ? 65535 : total_delay_ticks;  
        unsigned int delay_ticks_start = 65535 - delay_ticks_part;

        TL0 = delay_ticks_start & 0x0F;
        TH0 = delay_ticks_start >> 8;

        TR0 = 1; //Start the timer

        while(TF0 == 0);

        TR0 = 0; //Stop the timer
        TF0 = 0;

        total_delay_ticks -= delay_ticks_part;
    }
}

void LCD_Command(unsigned char cmd){
    RS_PIN = 0;
    LCD_DATA_BUS = cmd;
    
    EN_PIN = 1;
    delay_timer0_mode1(1);
    EN_PIN = 0;
}

void LCD_Data(unsigned char data){
    RS_PIN = 1;
    LCD_DATA_BUS = data;

    EN_PIN = 1;
    delay_timer0_mode1(1);
    EN_PIN = 0;
}

void LCD_String(char *str) {
    while(*str) {
        LCD_Data(*str++);
    }
}


void LCD_init(){
    RW_PIN = 0; //Set to LOW since we are not reading LCD display data(Can also connect to GND)
    LCD_Command(0x38); // 8-bit mode, 2 lines, 5x7 matrix
    LCD_Command(0x0C); // Display on, cursor off
    LCD_Command(0x06); // Increment cursor
    LCD_Command(0x01); // Clear display
    delay_timer0_mode1(2);
}

void main(void){
    LCD_init();
    LCD_String("Hello Max!");
    while(1){

        LED_PIN = 0;
        delay_timer0_mode1(500);
        LED_PIN = 1;
        delay_timer0_mode1(500);
    }
}