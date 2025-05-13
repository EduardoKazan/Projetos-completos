# Medidor de Corrente com Arduino e Sensor SCT-013

Este projeto implementa um medidor de corrente elétrica utilizando um Arduino e o sensor não invasivo SCT-013 (100A).

## Descrição

O sistema mede a corrente elétrica que passa por um condutor utilizando o sensor SCT-013 conectado ao Arduino. Os valores medidos são processados pela biblioteca EmonLib para calcular a corrente eficaz (Irms). O resultado é exibido em um display LCD Nokia 5110 (utilizando a biblioteca Adafruit_PCD8544) e também enviado para o monitor serial.

## Componentes principais

- Sensor de corrente não invasivo SCT-013 (100A)
- Arduino para processamento dos dados
- Display LCD Nokia 5110 para exibição dos valores
- Biblioteca EmonLib para cálculo da corrente eficaz

## Funcionalidades

- Medição contínua da corrente elétrica
- Exibição dos valores de corrente no display e no monitor serial
- Calibração do sensor para precisão na medição

Este projeto é útil para monitoramento de consumo elétrico em sistemas residenciais ou industriais de forma simples e eficiente.
