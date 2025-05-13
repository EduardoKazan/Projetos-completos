# Projeto Robo Controle PID

Este projeto implementa um algoritmo básico de controle PID aplicado a um robô móvel.

## Descrição

O robô move-se para frente medindo a distância de um possível obstáculo utilizando um sensor ultrassônico HC-SR04. Se a distância for inferior a 20 cm, o robô move-se para trás até atingir essa distância. O sistema possui dois modos de controle:

- Modo PID: utiliza um algoritmo Proporcional-Integral-Derivativo para ajustar a velocidade dos motores de forma suave.
- Modo On-Off: controle simples que move o robô para frente ou para trás com velocidade máxima baseado na distância medida.

## Componentes principais

- Sensor ultrassônico HC-SR04 para medição de distância
- Controle de motores com PWM e direção
- LEDs indicadores para os modos de operação
- Chave para seleção entre modo PID e modo On-Off

## Funcionalidades

- Medição contínua da distância até o obstáculo
- Controle PID para ajuste fino da velocidade dos motores
- Controle On-Off para resposta rápida
- Indicação visual do modo ativo via LEDs

Este projeto serve como base para aplicações de robótica móvel com controle PID para evitar obstáculos.
