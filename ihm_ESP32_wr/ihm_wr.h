/* ============================================================================

     IHMWR v.01 file.h

     Serial Interface with 74HC595
     LCD 16x2 with backlight
     auxiliary LED
     4 buttons

     Author: Dr. Eng. Wagner Rambo
     Date:   2024, February

============================================================================ */

#ifndef IHM_WR_H
#define IHM_WR_H

// --- Libraries ---
#include <Arduino.h>

// --- Hardware Mapping ---
#define CLK GPIO_NUM_18
#define DAT GPIO_NUM_19
#define LAT GPIO_NUM_21
#define BT1 GPIO_NUM_4
#define BT2 GPIO_NUM_32
#define BT3 GPIO_NUM_5
#define BT4 GPIO_NUM_34

// --- Constants ---
#define LD (1 << 0)
#define BL (1 << 1)
#define RS (1 << 2)
#define EN (1 << 3)

// --- Functions Prototypes ---
void __ms(unsigned long t);                    // Gera um delay em milissegundos
void slcd_write(unsigned char chr);            // Escreve caracteres na posição atual do LCD
void slcd_wr_po(unsigned char chr, char row, char col); // Escreve caracteres no LCD
void slcd_cmd(unsigned char cmd);              // Envia comandos para o LCD
void slcd_number(unsigned long num, char row, char col); // Converte um inteiro positivo para exibir no LCD
void slcd_init(void);                          // Inicializa o LCD no modo de 4 bits
void slcd_clear(void);                         // Limpa o LCD
void shift_reg(unsigned char byte_val);        // Controla o shift register
void send_nibble(unsigned char nib, char rsel, char bli, char led); // Envia cada nibble do byte separadamente
void sled_on(void);
void sled_off(void);
void sbacklight_on(void);
void sbacklight_off(void);
void slcd_opt(char disp, char cursor, char blink); // Configura ON (1) | OFF (0) para: display, cursor e blink
char keyboard(void);

#endif // IHM_WR_H