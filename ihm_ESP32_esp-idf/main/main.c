/* ============================================================================

     IHMWR v.01 main.c

     Serial Interface with 74HC595
     LCD 16x2 with back light
     auxiliary LED
     4 buttons

     IDE: Espressif IDE 2.6.0
     ESP32 DevKitV1

     Author: Dr. Eng. Wagner Rambo
     Date:   2024, February

============================================================================ */


// ============================================================================
// --- Libraries ---
#include <stdio.h>
#include <stdbool.h>
//#include "freertos/FreeRTOS.h"
//#include "freertos/task.h"
#include "driver/gpio.h"
//#include "esp_system.h"
#include "ihm_wr.h"


// ============================================================================
// --- Functions Prototypes ---
void select_(char *test_opt);                  //testa a escrita de um número inteiro no LCD
void number_test(void);                        //testa a escrita de um número inteiro no LCD
void keyboard_test(void);                      //teste do teclado imprime o número da tecla pressionada


// ============================================================================
// --- Main Function ---
void app_main(void)
{
  char tests = 0;


  gpio_set_direction(CLK, GPIO_MODE_OUTPUT);
  gpio_set_direction(DAT, GPIO_MODE_OUTPUT);
  gpio_set_direction(LAT, GPIO_MODE_OUTPUT);
  gpio_set_direction(BT1, GPIO_MODE_INPUT);
  gpio_set_direction(BT2, GPIO_MODE_INPUT);
  gpio_set_direction(BT3, GPIO_MODE_INPUT);
  gpio_set_direction(BT4, GPIO_MODE_INPUT);

  gpio_set_level(CLK, 0);
  gpio_set_level(DAT, 0);
  gpio_set_level(LAT, 0);



  slcd_init();
  slcd_opt(1,1,1);
  slcd_wr_po('W', 0, 4);
  slcd_write('R');
  slcd_write(' ');
  slcd_write('K');
  slcd_write('i');
  slcd_write('t');
  slcd_write('s');

  vTaskDelay(pdMS_TO_TICKS(100));

  slcd_opt(1,0,0);


  select_(&tests);

  while(1)
  {
    if(tests)
      number_test();
    else
      keyboard_test();

  } //end while


} //end main


// ============================================================================
// --- Functions ---


// ============================================================================
// --- number_test ---
// Testa a escrita de um número inteiro no LCD
void select_(char *test_opt)
{
  if(gpio_get_level(BT1))
  {
    slcd_wr_po('K', 1, 4);
    slcd_write('B');
    slcd_write(':');
    *test_opt = 0;

  } //end if

  else
  {
    slcd_wr_po('N', 1, 4);
    slcd_write(':');
    *test_opt = 1;

  } //end else

  (gpio_get_level(BT2)) ? sled_off()       : sled_on();
  (gpio_get_level(BT3)) ? sbacklight_off() : sbacklight_on();

} //end select



// ============================================================================
// --- number_test ---
// Testa a escrita de um número inteiro no LCD
void number_test(void)
{
  static unsigned val = 0;                     //valor inicial

  slcd_number(val++, 1, 6);
  vTaskDelay(pdMS_TO_TICKS(100));

} //end number_test



// ============================================================================
// --- keyboard_test ---
// Teste do teclado, imprime o número da tecla pressionada
void keyboard_test(void)
{
  static char kb = 0;

  kb = keyboard();

  switch(kb)
  {
    case 1:
      slcd_wr_po('1',1,10);
      break;
    case 2:
      slcd_wr_po('2',1,10);
      break;
    case 3:
      slcd_wr_po('3',1,10);
      break;
    case 4:
      slcd_wr_po('4',1,10);

  } //end switch


} //end keyboard_test















































// ============================================================================
// --- End of Program ---
