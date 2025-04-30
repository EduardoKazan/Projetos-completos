/* ============================================================================

     IHMWR v.01 file.cpp

     Serial Interface with 74HC595
     LCD 16x2 with backlight
     auxiliary LED
     4 buttons

     Author: Dr. Eng. Wagner Rambo
     Date:   2024, February

============================================================================ */

// --- Libraries ---
#include "ihm_wr.h"

// --- Global Variables ---
char sled = 0; // Mantém o estado atual do LED
char sbli = 0; // Mantém o estado atual do backlight

// --- Functions ---
void __ms(unsigned long t) {
  delay(t);
}

void slcd_write(unsigned char chr) {
  send_nibble(chr, 1, sbli, sled);
  chr <<= 4;
  send_nibble(chr, 1, sbli, sled);
}

void slcd_wr_po(unsigned char chr, char row, char col) {
  if (!row) {
    slcd_cmd(0x80 | col); // Envia comando para posicionar na coluna correta
    slcd_write(chr);
  } else {
    slcd_cmd(0xC0 | col); // Envia comando para posicionar na coluna correta
    slcd_write(chr);
  }
}

void slcd_cmd(unsigned char cmd) {
  send_nibble(cmd, 0, sbli, sled);
  cmd <<= 4;
  send_nibble(cmd, 0, sbli, sled);
}

void slcd_number(unsigned long num, char row, char col) {
  char dem, mil, cen, dez, uni; // Variáveis para o cálculo de cada dígito
  short no_zero = 0; // Variável para limpeza dos zeros à esquerda

  dem = (char)(num / 10000);
  mil = (char)(num % 10000 / 1000);
  cen = (char)(num % 1000 / 100);
  dez = (char)(num % 100 / 10);
  uni = (char)(num % 10);

  if (!dem && !no_zero)
    slcd_wr_po(' ', row, col);
  else {
    slcd_wr_po(dem + 0x30, row, col);
    no_zero = 1;
  }

  if (!mil && !no_zero)
    slcd_write(' ');
  else {
    slcd_write(mil + 0x30);
    no_zero = 1;
  }

  if (!cen && !no_zero)
    slcd_write(' ');
  else {
    slcd_write(cen + 0x30);
    no_zero = 1;
  }

  if (!dez && !no_zero)
    slcd_write(' ');
  else {
    slcd_write(dez + 0x30);
    no_zero = 1;
  }

  slcd_write(uni + 0x30);
}

void slcd_init(void) {
  __ms(48); // Tempo de estabilização recomendado (datasheet)
  send_nibble(0x30, 0, 0, 0); // Protocolo de inicialização
  __ms(5); // Tempo acima do sugerido (datasheet)
  send_nibble(0x30, 0, 0, 0); // Protocolo de inicialização
  __ms(150); // Tempo acima do sugerido (datasheet)
  send_nibble(0x30, 0, 0, 0); // Protocolo de inicialização
  send_nibble(0x20, 0, 0, 0); // LCD no modo de 4 bits
  slcd_cmd(0x28); // 5x8 pontos por caractere, duas linhas
  slcd_opt(1, 0, 0); // Liga o LCD, desliga o cursor, desliga o blink
  slcd_cmd(0x01); // Clear LCD
  slcd_cmd(0x06); // Modo de incremento de endereço para direita
  slcd_clear(); // Limpa o LCD
}

void slcd_clear(void) {
  slcd_cmd(0x02); // Return home
  slcd_cmd(0x01); // Clear LCD
}

void shift_reg(unsigned char byte_val) {
  for (int i = 7; i >= 0; i--) {
    (byte_val >> i) & 0x01 ? (digitalWrite(DAT, HIGH)) : (digitalWrite(DAT, LOW));
    delayMicroseconds(100);
    digitalWrite(CLK, HIGH);
    __ms(1);
    digitalWrite(CLK, LOW);
    delayMicroseconds(100);
  }

  digitalWrite(DAT, LOW);
  digitalWrite(LAT, HIGH);
  __ms(1);
  digitalWrite(LAT, LOW);
}

void send_nibble(unsigned char nib, char rsel, char bli, char led) {
  static unsigned char sbyte = 0x00;

  sbyte = (nib & (1 << 7)) |
          (nib & (1 << 6)) |
          (nib & (1 << 5)) |
          (nib & (1 << 4));

  rsel ? (sbyte |= RS) : (sbyte &= ~RS);
  bli ? (sbyte |= BL) : (sbyte &= ~BL);
  led ? (sbyte |= LD) : (sbyte &= ~LD);

  shift_reg(sbyte | EN);
  delayMicroseconds(100);
  shift_reg(sbyte & ~EN);
  delayMicroseconds(100);
}

void slcd_opt(char disp, char cursor, char blink) {
  static char opt = 0x08;

  disp ? (opt |= (1 << 2)) : (opt &= ~(1 << 2));
  cursor ? (opt |= (1 << 1)) : (opt &= ~(1 << 1));
  blink ? (opt |= (1 << 0)) : (opt &= ~(1 << 0));
  slcd_cmd(opt);
}

void sled_on(void) {
  sled = 1;
  slcd_cmd(0x06);
}

void sled_off(void) {
  sled = 0;
  slcd_cmd(0x06);
}

void sbacklight_on(void) {
  sbli = 1;
  slcd_cmd(0x06);
}

void sbacklight_off(void) {
  sbli = 0;
  slcd_cmd(0x06);
}

char keyboard(void) {
  static unsigned char flags = 0x00; // Indicador de botão acionado

  if (!(digitalRead(BT1))) { // Botão 1 pressionado?
    flags |= (1 << 1); // Sim, seta flag bit 1
  }

  if ((digitalRead(BT1)) && (flags & (1 << 1))) { // Botão 1 solto e flag 1 setada?
    flags &= ~(1 << 1); // Limpa a flag 1
    __ms(50); // Anti-bouncing
    return 1; // Retorna 1, indicando botão 1 pressionado
  }

  if (!(digitalRead(BT2))) { // Botão 2 pressionado?
    flags |= (1 << 2); // Sim, seta flag bit 2
  }

  if ((digitalRead(BT2)) && (flags & (1 << 2))) { // Botão 2 solto e flag 2 setada?
    flags &= ~(1 << 2); // Limpa a flag 2
    __ms(50); // Anti-bouncing
    return 2; // Retorna 2, indicando botão 2 pressionado
  }

  if (!(digitalRead(BT3))) { // Botão 3 pressionado?
    flags |= (1 << 3); // Sim, seta flag bit 3
  }

  if ((digitalRead(BT3)) && (flags & (1 << 3))) { // Botão 3 solto e flag 3 setada?
    flags &= ~(1 << 3); // Limpa a flag 3
    __ms(50); // Anti-bouncing
    return 3; // Retorna 3, indicando botão 3 pressionado
  }

  if (!(digitalRead(BT4))) { // Botão 4 pressionado?
    flags |= (1 << 4); // Sim, seta flag bit 4
  }

  if ((digitalRead(BT4)) && (flags & (1 << 4))) { // Botão 4 solto e flag 4 setada?
    flags &= ~(1 << 4); // Limpa a flag 4
    __ms(50); // Anti-bouncing
    return 4; // Retorna 4, indicando botão 4 pressionado
  }

  return 0;
}