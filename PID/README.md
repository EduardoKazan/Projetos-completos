# Projeto PID para Arduino

Este projeto implementa um controlador PID simples para Arduino, utilizado para controle de temperatura.

## Descrição

O sistema lê a temperatura de um sensor analógico conectado ao pino A1, processa o valor utilizando um algoritmo PID, e gera um sinal PWM de controle no pino 3 para atuar sobre um atuador (por exemplo, um aquecedor).

## Componentes principais

- Sensor analógico de temperatura (conectado ao pino A1)
- Saída PWM para controle (pino 3)
- Classe PID para cálculo do controle

## Funcionalidades

- Leitura contínua da temperatura
- Processamento PID para ajuste do controle
- Saída PWM para controle do dispositivo

Este projeto serve como base para aplicações de controle de temperatura e outros sistemas que necessitem de controle PID em microcontroladores Arduino.
