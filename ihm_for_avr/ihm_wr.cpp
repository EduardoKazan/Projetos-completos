/* ============================================================================

     IHMWR v.01 ihm_wr.cpp

     Serial Interface with 74HC595
     LCD 16x2 with backlight
     auxiliary LED
     4 buttons

     Author: Dr. Eng. Wagner Rambo
     Date:   2024, February

============================================================================ */

// ============================================================================
// --- Libraries ---
#include "ihm_wr.h"

// ============================================================================
// --- Global Variables ---
char sled = 0; // mantém o estado atual do LED
char sbli = 0; // mantém o estado atual do backlight

// ============================================================================
// --- Functions ---

// ============================================================================
// --- slcd_write ---
// escreve caracteres na posição atual do LCD
void slcd_write(unsigned char chr)
{
  send_nibble(chr, 1, sbli, sled);
  chr <<= 4;
  send_nibble(chr, 1, sbli, sled);
}

// ============================================================================
// --- slcd_wr_po ---
// escreve caracteres, de acordo com a linha e a coluna especificadas
void slcd_wr_po(unsigned char chr, char row, char col)
{
  if (!row) // linha 0?
  {
    slcd_cmd(0x80 | col); // envia comando para posicionar na coluna correta
    slcd_write(chr);
  }
  else // senão, é a linha 1
  {
    slcd_cmd(0xC0 | col); // envia comando para posicionar na coluna correta
    slcd_write(chr);
  }
}

// ============================================================================
// --- slcd_cmd ---
// envia comandos para o LCD
void slcd_cmd(unsigned char cmd)
{
  send_nibble(cmd, 0, sbli, sled);
  cmd <<= 4;
  send_nibble(cmd, 0, sbli, sled);
}

// ============================================================================
// --- slcd_number ---
// converte um inteiro positivo para exibir no LCD na linha e na coluna especificadas
void slcd_number(unsigned long num, char row, char col)
{
  char dem, mil, cen, dez, uni; // variáveis para o cálculo de cada dígito
  short no_zero = 0; // variável para limpeza dos zeros à esquerda
  
  dem = (char)(num / 10000);
  mil = (char)(num % 10000 / 1000);
  cen = (char)(num % 1000 / 100);
  dez = (char)(num % 100 / 10);
  uni = (char)(num % 10);
  
  if (!dem && !no_zero)
    slcd_wr_po(' ', row, col);
  else
  {
    slcd_wr_po(dem + 0x30, row, col);
    no_zero = 1;
  }
  
  if (!mil && !no_zero)
    slcd_write(' ');
  else
  {
    slcd_write(mil + 0x30);
    no_zero = 1;
  }
  
  if (!cen && !no_zero)
    slcd_write(' ');
  else
  {
    slcd_write(cen + 0x30);
    no_zero = 1;
  }

  if (!dez && !no_zero)
    slcd_write(' ');
  else
  {
    slcd_write(dez + 0x30);
    no_zero = 1;
  }
  
  slcd_write(uni + 0x30);
}

// ============================================================================
// --- slcd_init ---
// inicializa o LCD no modo de 4 bits
void slcd_init(void)
{
  __ms(48); // tempo de estabilização recomendado (datasheet)
  send_nibble(0x30, 0, 0, 0); // protocolo de inicialização
  __ms(5); // tempo acima do sugerido (datasheet)
  send_nibble(0x30, 0, 0, 0); // protocolo de inicialização
  __us(150); // tempo acima do sugerido (datasheet)
  send_nibble(0x30, 0, 0, 0); // protocolo de inicialização
  send_nibble(0x20, 0, 0, 0); // lcd no modo de 4 bits
  slcd_cmd(0x28); // 5x8 pontos por caractere, duas linhas
  slcd_opt(1, 0, 0); // liga o LCD, desliga o cursor, desliga o blink
  slcd_cmd(0x01); // clear LCD
  slcd_cmd(0x06); // modo de incremento de endereço para direita
  slcd_clear(); // limpa o LCD
}

// ============================================================================
// --- slcd_clear ---
// limpa o LCD
void slcd_clear(void)
{
  slcd_cmd(0x02); // return home
  slcd_cmd(0x01); // clear lcd
}

// ============================================================================
// --- shift_reg ---
// controla o shift register
void shift_reg(unsigned char byte_val)
{
  register int i; // iterations variable
  
  for (i = 7; i >= 0; i--)
  {
    (byte_val >> i) & 0x01 ?
      (PORTMCU |= DAT) :
      (PORTMCU &= ~DAT);
    __us(100);
    PORTMCU |= CLK;
    __ms(1);
    PORTMCU &= ~CLK;
    __us(100);
  }
  
  PORTMCU &= ~DAT;
  PORTMCU |= LAT;
  __ms(1);
  PORTMCU &= ~LAT;
}

// ============================================================================
// --- send_nibble ---
// envia cada nibble do byte separadamente
void send_nibble(unsigned char nib, char rsel, char bli, char led)
{
  static unsigned char sbyte = 0x00;
  
  sbyte = (nib & (1 << 7)) |
          (nib & (1 << 6)) |
          (nib & (1 << 5)) |
          (nib & (1 << 4));

  rsel ? (sbyte |= RS) : (sbyte &= ~RS);
  bli  ? (sbyte |= BL) : (sbyte &= ~BL);
  led  ? (sbyte |= LD) : (sbyte &= ~LD);
  
  shift_reg(sbyte | EN);
  __us(100);
  shift_reg(sbyte & ~EN);
  __us(100);
}

// ============================================================================
// --- slcd_opt ---
// configura ON (1) | OFF (0) para: display, cursor e blink
void slcd_opt(char disp, char cursor, char blink)
{
  static char opt = 0x08;
  
  disp   ? (opt |= (1 << 2)) : (opt &= ~(1 << 2));
  cursor ? (opt |= (1 << 1)) : (opt &= ~(1 << 1));
  blink  ? (opt |= (1 << 0)) : (opt &= ~(1 << 0));
  slcd_cmd(opt);
}

// ============================================================================
// --- sled_on ---
// liga LED
void sled_on(void)
{
  sled = 1;
  slcd_cmd(0x06);
}

// ============================================================================
// --- sled_off ---
// desliga LED
void sled_off(void)
{
  sled = 0;
  slcd_cmd(0x06);
}

// ============================================================================
// --- sbacklight_on ---
// liga backlight
void sbacklight_on(void)
{
  sbli = 1;
  slcd_cmd(0x06);
}

// ============================================================================
// --- sbacklight_off ---
// desliga backlight
void sbacklight_off(void)
{
  sbli = 0;
  slcd_cmd(0x06);
}

// ============================================================================
// --- keyboard ---
// leitura do teclado, retorna tecla acionada
char keyboard(volatile unsigned char *port)
{
  static unsigned char flags = 0x00; // indicador de botão acionado
  
  if (!(*port & BT1)) // botão 1 pressionado?
    flags |= (1 << 1); // sim, seta flag bit 1
  
  if ((*port & BT1) && (flags & (1 << 1))) // botão 1 solto e flag 1 setada?
  {
    flags &= ~(1 << 1); // limpa a flag 1
    __ms(50); // anti-bouncing
    return 1; // retorna 1, indicando botão 1 pressionado
  }
  
  if (!(*port & BT2)) // botão 2 pressionado?
    flags |= (1 << 2); // sim, seta flag bit 2

  if ((*port & BT2) && (flags & (1 << 2))) // botão 2 solto e flag 2 setada?
  {
    flags &= ~(1 << 2); // limpa a flag 2
    __ms(50); // anti-bouncing
    return 2; // retorna 2, indicando botão 2 pressionado
  }
  
  if (!(*port & BT3)) // botão 3 pressionado?
    flags |= (1 << 3); // sim, seta flag bit 3

  if ((*port & BT3) && (flags & (1 << 3))) // botão 3 solto e flag 3 setada?
  {
    flags &= ~(1 << 3); // limpa a flag 3
    __ms(50); // anti-bouncing
    return 3; // retorna 3, indicando botão 3 pressionado
  }
  
  if (!(*port & BT4)) // botão 4 pressionado?
    flags |= (1 << 4); // sim, seta flag bit 4

  if ((*port & BT4) && (flags & (1 << 4))) // botão 4 solto e flag 4 setada?
  {
    flags &= ~(1 << 4); // limpa a flag 4
    __ms(50); // anti-bouncing
    return 4; // retorna 4, indicando botão 4 pressionado
  }
  
  return 0; // nenhum botão pressionado
}

// ============================================================================
// --- End of Program ---