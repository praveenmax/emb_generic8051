#include <8051.h>       // Include the 8051 microcontroller header file
#define LCD P2           // Define the port P2 as LCD data port
#define RS P3_0          // Define pin P3.0 as RS (Register Select)
#define EN  P3_1          // Define pin P3.1 as EN (Enable)

unsigned char txt[11] = "PraveenMax!";  // Data to display on the LCD

// Delay function
void delay() {   
   int k;   
   for (k = 0; k <= 2000; k++); 
} 

// LCD subroutine for command and data transmission
void lcd(char a, short int b) {   
   LCD = a;           // Place byte 'a' in D0-D7 lines of LCD
   RS = b;            // Set RS: 0 for command, 1 for data
   EN = 1;            // Enable the LCD
   delay();           // Delay to ensure the LCD processes the command/data
   EN = 0;            // Disable the LCD
}

// Main function
void main() {
   int i = 0;

   // Initializing the LCD with some commands
   lcd(0x38, 0);      // Function set: 8-bit, 2 line, 5x7 dots
   lcd(0x0f, 0);      // Display on, cursor on, blinking cursor
   lcd(0x01, 0);      // Clear display
   lcd(0x02, 0);      // Return home
   lcd(0x80, 0);      // Set DDRAM address to 0x80 (first line)

   // Transmitting data to the LCD
   for (i = 0; i < 11; i++) {
      lcd(txt[i], 1); // Send each character to the LCD
   }

   while (1){
    
   }         // Infinite loop to keep the program running
}
