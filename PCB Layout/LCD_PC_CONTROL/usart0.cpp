/* ===========================================================================

    Projeto da Aula 7 do Módulo 2 Curso AVR Projetos Profissionais
	
	BIBLIOTECA USART AVR

    ARQUIVO usart0.c
    
    

    MCU:   Atmega328p
    Clock: 16MHz Cristal Externo

    Compilador: Microchip Studio 7.0.2542
    Autor: Dr. Eng. Wagner Rambo
    Data de criação: Março de 2022
    Última atualização: 26/03/2022

============================================================================ */


// ============================================================================
// --- Biblioteca ---
#include "usart0.h"



// ============================================================================
// --- Variáveis Globais ---
volatile uint8_t usart_run = 1;                //1 para usart rodando, 0 para usart ocupada
volatile char rx_buffer[SIZEBUFF] = {0x00};    //buffer para recepção serial
volatile uint16_t rx_buff = 0;                 //contador de bytes


// ============================================================================
// --- Interrupções USART ---
ISR(USART_RX_vect)
{
  static uint16_t cnt_buff = 0;                //contador local de endereço para o buffer rx
  
  rx_buffer[cnt_buff] = UDR0;                  //armazena o byte recebido no endereço atual do buffer de rx
  rx_buff++;                                   //incrementa o contador global de bytes recebidos
  cnt_buff++;                                  //incrementa o contador local de endereços para o buffer de rx
  
  if(cnt_buff>=SIZEBUFF)
    cnt_buff = 0;
    	
}

ISR(USART_TX_vect)
{
  usart_run = 1;                               //ocorrência da transmissão	
}


// ============================================================================
// --- Desenvolvimento das Funções USART ---


// ============================================================================
// --- usart0_init ---
// Inicialização da USART
void usart0_init(uint16_t bps, uint8_t fast)
{
  
  if(fast)                                     //se fast verdadeiro, double speed
  {
	UCSR0A |= (1<<U2X0);                       //double speed 
	UBRR0 = (F_CPU/(8UL*bps))-1;               //cálculo do baud rate  
	  
  }
  
  else                                         //senão, operação normal da USART
  {
	UCSR0A &= ~(1<<U2X0);                      //modo normal
	UBRR0 = (F_CPU/(16UL*bps))-1;              //cálculo do baud rate para o modo normal  
	  
  }
  
  UCSR0B |= (1<<RXCIE0) |                      //habilita interrupção para RX
            (1<<TXCIE0) |                      //habilita interrupção para TX
			(1<<RXEN0)  |                      //habilita recepção USART
			(1<<TXEN0);                        //habilita transmissão da USART
			
			
  UCSR0C = 0x06;                               //USART assíncrona, sem paridade, 8 bits de dados, 1 stop bit
  
  sei();                                       //habilita interrupção global
  
	
} //usart0_init


// ============================================================================
// --- usart0_write ---
// Função para enviar 1 byte por USART
void usart0_write(char byte_tx)
{
  while(!usart_run);                           //aguarda usart liberar
  
  usart_run = 0;                               //ocupa usart
  
  UDR0 = byte_tx;
	
} //usart0_write


// ============================================================================
// --- usart0_print ---
// Função para enviar 1 string por USART
void usart0_print(char *str)
{
   uint16_t i;
   
   for(i=0;str[i]!='\0';i++)
     usart0_write(str[i]);
	 
}


// ============================================================================
// --- usart0_println ---
// Função para enviar 1 string por USART com o "enter"
void usart0_println(char *str)
{
  uint16_t i;
	
  for(i=0;str[i]!='\0';i++)
	usart0_write(str[i]);
	
  usart0_write(0x0A);
  usart0_write(0x0D);	
	
}


// ============================================================================
// --- usart0_read ---
// Lê os bytes recebidos via USART
char usart0_read()
{
  static uint16_t buff_lo = 0;
  char byte_rx = 0;
  
  byte_rx = rx_buffer[buff_lo];
  buff_lo++;
  rx_buff--;
  
  if(buff_lo>=SIZEBUFF)
    buff_lo = 0;
	
  return byte_rx;
  	
}


// ============================================================================
// --- usart0_cnt ---
// Retorna o número de bytes recebidos até o momento
uint16_t usart0_cnt()
{
  return rx_buff;	
}




/* ============================================================================

                                       _
                                      / \
                                     |oo >      <-- (USART, I love it!)
                                     _\=/_
                    ___         #   /  _  \   #
                   /<> \         \\//|/.\|\\//
                 _|_____|_        \/  \_/  \/
                | | === | |          |\ /|
                |_|  0  |_|          \_ _/
                 ||  0  ||           | | |
                 ||__*__||           | | |
                |* \___/ *|          []|[]
                /=\ /=\ /=\          | | |
________________[_]_[_]_[_]_________/_]_[_\_______________________________


============================================================================ */
/* --- Final do Arquivo usart0.c --- */
