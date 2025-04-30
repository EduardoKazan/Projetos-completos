/* ============================================================================

     IHMWR v.01 ihm_wr.h
     
     Serial Interface with 74HC595
     LCD 16x2 with backlight
     auxiliary LED
     4 buttons
     
     Author: Dr. Eng. Wagner Rambo
     Date:   2024, February

============================================================================ */

#ifndef  IHM_WR_H
#define  IHM_WR_H

// ============================================================================
// --- Libraries ---
#include <Arduino.h>

// ============================================================================
// --- Hardware Mapping ---
#define    CLK      (1<<0)
#define    DAT      (1<<1)
#define    LAT      (1<<2)
#define    BT1      (1<<4)
#define    BT2      (1<<5)
#define    BT3      (1<<6)
#define    BT4      (1<<7)
#define    PORTMCU  PORTD

// ============================================================================
// --- Macros ---
#define   __ms(t)  delay(t)
#define   __us(t)  delayMicroseconds(t)

// ============================================================================
// --- Constants ---
#define   LD   (1<<0)
#define   BL   (1<<1)
#define   RS   (1<<2)
#define   EN   (1<<3)

// ============================================================================
// --- Functions Prototypes ---
void slcd_write(unsigned char chr);
void slcd_wr_po(unsigned char chr, char row, char col);
void slcd_cmd(unsigned char cmd);
void slcd_number(unsigned long num, char row, char col);
void slcd_init(void);
void slcd_clear(void);
void shift_reg(unsigned char byte_val);
void send_nibble(unsigned char nib, char rsel, char bli, char led);
void sled_on(void);
void sled_off(void);
void sbacklight_on(void);
void sbacklight_off(void);
void slcd_opt(char disp, char cursor, char blink);
char keyboard(volatile unsigned char *port);

#endif //IHM_WR_H

// ============================================================================
// --- End of Program ---