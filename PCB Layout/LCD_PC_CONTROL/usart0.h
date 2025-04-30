/* ===========================================================================

    Projeto da Aula 7 do Módulo 2 Curso AVR Projetos Profissionais
        
        BIBLIOTECA USART AVR

    ARQUIVO usart0.h
    
    
    

    MCU:   Atmega328p
    Clock: 16MHz Cristal Externo

    Compilador: Microchip Studio 7.0.2542
    Autor: Dr. Eng. Wagner Rambo
    Data de criação: Março de 2022
    Última atualização: 26/03/2022

============================================================================ */

// ============================================================================
// --- Frequência do MCU ---
#define   F_CPU   16000000UL


// ============================================================================
// --- Bibliotecas ---
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


// ============================================================================
// --- Protótipo das Funções USART ---
void usart0_init(uint16_t bps, uint8_t fast);
void usart0_write(char byte_tx);
void usart0_print(char *str);
void usart0_println(char *str);
char usart0_read();
uint16_t usart0_cnt();


// ============================================================================
// --- Constantes Auxiliares ---
#define  SIZEBUFF  64

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
/* --- Final do Arquivo usart0.h --- */