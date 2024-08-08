#include <8051.h>

//Clock stuffs
#define FOSC 11059200UL
#define TICKS_PER_MS (FOSC/12/1000)

//LCD Stuffs
#define RS_PIN P2_0
#define RW_PIN P2_1
#define EN_PIN P2_2
#define LCD_DATA_BUS P1

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
    LCD_Command(0x02); // Return Home
    LCD_Command(0x01); // Clear display
    LCD_Command(0x0C); // Display on, cursor off
    LCD_Command(0x06); // Increment cursor
    LCD_Command(0x80); // Text starts from Line 1 
   // LCD_Command(0xC0); // Text starts from Line 2 
    //LCD_Command(0x8F); // Custom location test
    delay_timer0_mode1(2);
}

void main(void){
    LCD_init();
    LCD_Command(0x80 + 3); //Set text position to Line 1 at 3 offset.
    LCD_String("Hello Max!");

    unsigned char text_startpos_line2 = 0xC0;
    unsigned char current_text_pos = 0;

    while(1){

        // LED_PIN = 0;
        // delay_timer0_mode1(500);
        // LED_PIN = 1;
        // delay_timer0_mode1(500);

        //Testing
        //LCD_Command(text_startpos_line2);
        // LCD_Data('A');

        //Displaying one word at a time. 
        for(current_text_pos = 0; current_text_pos < 16 ; current_text_pos++)
        {
          LCD_Command(text_startpos_line2 + (current_text_pos)); 
          LCD_Data('>');
          delay_timer0_mode1(100);
        }

        //Reset the current position so that the text starts from position 0 
        current_text_pos=0;

        //Clear the old text
        LCD_Command(text_startpos_line2); 
        for(int i=0;i<16;i++)
        {
           LCD_Data(' '); //Space will remove the char
           delay_timer0_mode1(100); // Delay needed to better visuals
        }
    }
}