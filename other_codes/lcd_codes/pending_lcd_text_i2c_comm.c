#include <8051.h>

#define I2C_SCL P2_1  // SCL pin
#define I2C_SDA P2_2  // SDA pin
#define LCD_ADDR 0x3F // I2C address of the LCD (adjust if necessary)

void I2C_delay() {
    unsigned int i;
    for (i = 0; i < 100; i++); // Adjust for proper timing
}

void I2C_start() {
    I2C_SDA = 1;
    I2C_SCL = 1;
    I2C_delay();
    I2C_SDA = 0;
    I2C_delay();
    I2C_SCL = 0;
}

void I2C_stop() {
    I2C_SDA = 0;
    I2C_SCL = 1;
    I2C_delay();
    I2C_SDA = 1;
    I2C_delay();
}

void I2C_write(unsigned char data) {
    unsigned char i;
    for (i = 0; i < 8; i++) {
        I2C_SDA = (data & 0x80) ? 1 : 0;
        data <<= 1;
        I2C_SCL = 1;
        I2C_delay();
        I2C_SCL = 0;
    }
    I2C_SDA = 1; // ACK
    I2C_SCL = 1;
    I2C_delay();
    I2C_SCL = 0;
}

void lcd_command(unsigned char cmd) {
    I2C_start();
    I2C_write(LCD_ADDR);
    I2C_write(0x00);       // Control byte: Co = 0, RS = 0
    I2C_write(cmd);
    I2C_stop();
}

void lcd_data(unsigned char data) {
    I2C_start();
    I2C_write(LCD_ADDR);
    I2C_write(0x40);       // Control byte: Co = 0, RS = 1
    I2C_write(data);
    I2C_stop();
}

void lcd_init() {
    lcd_command(0x38);     // Function set: 8-bit mode, 2 lines, 5x8 dots
    lcd_command(0x0C);     // Display on, cursor off
    lcd_command(0x06);     // Entry mode set: increment cursor
    lcd_command(0x01);     // Clear display
}

void lcd_print(char *str) {
    while (*str) {
        lcd_data(*str++);
    }
}

void main() {
    lcd_init();            // Initialize LCD
    lcd_print("Hello, World!");  // Print string on LCD

    while (1) {
        // Loop forever
    }
}
