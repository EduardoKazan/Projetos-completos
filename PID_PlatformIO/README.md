# Projeto PID com PlatformIO para ESP32

Este projeto implementa um controlador PID para um microcontrolador ESP32 utilizando o framework Arduino no PlatformIO.

## Descrição

O sistema lê a temperatura de um sensor analógico conectado ao pino 35, processa o valor utilizando um algoritmo PID, e gera um sinal PWM de controle no pino 3 para atuar sobre um atuador (por exemplo, um aquecedor).

A classe PID implementa o cálculo do controle proporcional, integral e derivativo para ajustar a saída conforme o erro entre o valor medido e o ponto de ajuste.

## Componentes principais

- Sensor analógico de temperatura (conectado ao pino 35)
- Saída PWM para controle (pino 3)
- Classe PID para cálculo do controle
- Plataforma PlatformIO com framework Arduino para desenvolvimento

## Funcionalidades

- Leitura contínua da temperatura
- Processamento PID para ajuste do controle
- Saída PWM para controle do dispositivo

Este projeto serve como base para aplicações de controle de temperatura e outros sistemas que necessitem de controle PID em microcontroladores ESP32.
