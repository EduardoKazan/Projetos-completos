/* ============================================================================

     IHMWR v.01 main.ino

     Serial Interface with 74HC595
     LCD 16x2 with back light
     auxiliary LED
     4 buttons

     Author: Dr. Eng. Wagner Rambo
     Date:   2024, February

============================================================================ */

// --- Libraries ---
#include <Arduino.h>
#include "ihm_wr.h"

// --- Functions Prototypes ---
void select_(char *test_opt);                  // Testa a escrita de um número inteiro no LCD
void number_test(void);                        // Testa a escrita de um número inteiro no LCD
void keyboard_test(void);                      // Teste do teclado imprime o número da tecla pressionada

// --- Main Function ---
void setup() {
  char tests = 0;

  pinMode(CLK, OUTPUT);
  pinMode(DAT, OUTPUT);
  pinMode(LAT, OUTPUT);
  pinMode(BT1, INPUT);
  pinMode(BT2, INPUT);
  pinMode(BT3, INPUT);
  pinMode(BT4, INPUT);

  digitalWrite(CLK, LOW);
  digitalWrite(DAT, LOW);
  digitalWrite(LAT, LOW);

  slcd_init();
  slcd_opt(1, 1, 1);
  slcd_wr_po('W', 0, 4);
  slcd_write('R');
  slcd_write(' ');
  slcd_write('K');
  slcd_write('i');
  slcd_write('t');
  slcd_write('s');

  delay(100);
  slcd_opt(1, 0, 0);

  select_(&tests);
}

void loop() {
  static char tests = 0; // Mover a variável para o escopo global

  if (tests)
    number_test();
  else
    keyboard_test();
}

// --- Functions ---
void select_(char *test_opt) {
  if (digitalRead(BT1)) {
    slcd_wr_po('K', 1, 4);
    slcd_write('B');
    slcd_write(':');
    *test_opt = 0;
  } else {
    slcd_wr_po('N', 1, 4);
    slcd_write(':');
    *test_opt = 1;
  }

  (digitalRead(BT2)) ? sled_off() : sled_on();
  (digitalRead(BT3)) ? sbacklight_off() : sbacklight_on();
}

void number_test(void) {
  static unsigned val = 0; // Valor inicial
  slcd_number(val++, 1, 6);
  delay(100);
}

void keyboard_test(void) {
  static char kb = 0;
  kb = keyboard();

  switch (kb) {
    case 1:
      slcd_wr_po('1', 1, 10);
      break;
    case 2:
      slcd_wr_po('2', 1, 10);
      break;
    case 3:
      slcd_wr_po('3', 1, 10);
      break;
    case 4:
      slcd_wr_po('4', 1, 10);
      break;
  }
}