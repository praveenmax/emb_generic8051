#include <8051.h>

// Define pins for CLK and DIO
#define CLK P2_0
#define DIO P2_1

// Segment codes for digits 0-9 (common anode)
unsigned char segment_codes[] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

void TM1637_start();
void TM1637_stop();
void TM1637_write_byte(unsigned char data);
void TM1637_display_digit(unsigned char position, unsigned char digit);

void format_number(unsigned int number, unsigned char* digits);

// Start condition for TM1637
void TM1637_start() {
    DIO = 1;
    CLK = 1;
    DIO = 0;
    CLK = 0;
}

// Stop condition for TM1637
void TM1637_stop() {
    CLK = 0;
    DIO = 0;
    CLK = 1;
    DIO = 1;
}

// Write a byte to TM1637
void TM1637_write_byte(unsigned char data) {
    for (unsigned char i = 0; i < 8; i++) {
        CLK = 0;
        DIO = (data & 0x01);
        data >>= 1;
        CLK = 1;
    }
    // Acknowledge bit
    CLK = 0;
    DIO = 1;
    CLK = 1;
    while (DIO);  // Wait for ACK
    CLK = 0;
}

// Display a digit at a specific position
void TM1637_display_digit(unsigned char position, unsigned char digit) {
    TM1637_start();
    TM1637_write_byte(0x44);  // Command to set data (fixed address)
    TM1637_stop();
    
    TM1637_start();
    TM1637_write_byte(0xC0 | position);  // Address command (0xC0 for address, OR with position)
    TM1637_write_byte(segment_codes[digit]);
    TM1637_stop();
    
    TM1637_start();
    TM1637_write_byte(0x88);  // Display control command (0x8X, X=brightness)
    TM1637_stop();
}

// Function to format a number with leading zeroes and split into digits
void format_number(unsigned int number, unsigned char* digits) {
    // Format number as 4-digit string with leading zeroes
    digits[3] = number % 10;            // Ones place
    digits[2] = (number / 10) % 10;     // Tens place
    digits[1] = (number / 100) % 10;    // Hundreds place
    digits[0] = (number / 1000) % 10;   // Thousands place
}


void main() {
    unsigned char number[4] = {5,5,7,8};  // Example number to display
    unsigned int count = 0;
    unsigned char digits[4];  

    // Keep the display on
    while (1){
        count = 0;
        while(count < 10000)
        {
            format_number(count, digits);

            for(unsigned char i = 0; i < 4; i++)
                TM1637_display_digit(i, digits[i]);

            count++;
        }
    }  
}
