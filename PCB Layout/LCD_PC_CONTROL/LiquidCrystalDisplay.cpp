#include "LiquidCrystalDisplay.h"

#define F_CPU 16000000UL
#include <util/delay.h>

#define LCD_RS 0
#define LCD_RW 1
#define LCD_EN 2

#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

static const unsigned char LCD_CLEAR_DISPLAY = 0x01;
static const unsigned char LCD_RETURN_HOME = 0x02;
static const unsigned char LCD_ENTRY_MODE_SET = 0x04;
static const unsigned char LCD_CURSOR_DISPLAY_SHIFT = 0x07;
static const unsigned char LCD_FUNCTION_SET = 0x20;
static const unsigned char LCD_SET_CGRAM_ADDRESS = 0x40;
static const unsigned char LCD_SET_DDRAM_ADDRESS = 0x80;

volatile unsigned char* const PORTD = (unsigned char*) 0x03;
volatile unsigned char* const DDRD = (unsigned char*) 0x02;
volatile unsigned char* const PIND = (unsigned char*) 0x00;

LiquidCrystalDisplay::LiquidCrystalDisplay() {
    _cols = 0;
    _rows = 0;
}

void LiquidCrystalDisplay::begin(unsigned char cols, unsigned char rows) {
    _cols = cols;
    _rows = rows;

    // Set up the LCD pins as outputs
    *DDRD |= (1 << LCD_RS) | (1 << LCD_RW) | (1 << LCD_EN) |
               (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) |
               (1 << LCD_D7);

    // Initialize the LCD
    _delay_ms(48);
    sendNibble(0x03, 0);
    _delay_ms(5);
    sendNibble(0x03, 0);
    _delay_us(150);
    sendNibble(0x03, 0);
    sendNibble(0x02, 0);
    command(LCD_FUNCTION_SET | (_cols - 1) | (_rows - 1) << 3);
    command(LCD_ENTRY_MODE_SET | (1 << 1));
    clear();
}

void LiquidCrystalDisplay::clear() {
    command(LCD_CLEAR_DISPLAY);
}

void LiquidCrystalDisplay::setCursor(unsigned char col, unsigned char row) {
    if (row == 0) {
        command(LCD_SET_DDRAM_ADDRESS | col);
    } else {
        command(LCD_SET_DDRAM_ADDRESS | (_cols + col));
    }
}

void LiquidCrystalDisplay::write(unsigned char data) {
    *PORTD &= ~(1 << LCD_RW);
    *PORTD |= (1 << LCD_RS);
    sendNibble(data >> 4, 1);
    sendNibble(data & 0x0F, 1);
}

void LiquidCrystalDisplay::command(unsigned char cmd) {
    *PORTD &= ~(1 << LCD_RS);
    *PORTD &= ~(1 << LCD_RW);
    sendNibble(cmd >> 4, 0);
    sendNibble(cmd & 0x0F, 0);
}

void LiquidCrystalDisplay::printNumber(int num, unsigned char row, unsigned char col) {
    char str[16];
    sprintf(str, "%d", num);
    printText(str, row, col);
}

void LiquidCrystalDisplay::printText(const char* text, unsigned char row, unsigned char col) {
    setCursor(col, row);
    while (*text != '\0') {
        write(*text);
        text++;
    }
}

void LiquidCrystalDisplay::sendNibble(unsigned char nibble, unsigned char isData) {
    *PORTD &= ~((1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7));
    *PORTD |= (nibble & 0x0F) << 4;

    if (isData) {
        *PORTD |= (1 << LCD_RS);
    } else {
        *PORTD &= ~(1 << LCD_RS);
    }
    pulseEnable();

    *PORTD &= ~((1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7));
    *PORTD |= (nibble & 0x0F);

    if (isData) {
        *PORTD |= (1 << LCD_RS);
    } else {
        *PORTD &= ~(1 << LCD_RS);
    }
    pulseEnable();
}

void LiquidCrystalDisplay::pulseEnable() {
    *PORTD |= (1 << LCD_EN);
    _delay_us(1200);
    *PORTD &= ~(1 << LCD_EN);
    _delay_us(1200);
}