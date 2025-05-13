# Projeto ReceiveAndSend - Arduino IR Remote

Este projeto implementa a funcionalidade de receber e enviar sinais infravermelhos (IR) utilizando um microcontrolador Arduino.

## Descrição

O sistema grava o último sinal IR recebido ao pressionar um botão e o reproduz quando o botão é pressionado novamente. A lógica é a seguinte:

- Se o botão estiver pressionado, o código IR armazenado é enviado.
- Se um código IR for recebido, ele é gravado para uso futuro.
- Se o protocolo do sinal IR for desconhecido ou não habilitado, o sinal é armazenado como dados brutos para envio posterior.

O projeto utiliza um detector/demodulador IR conectado ao pino de entrada definido, um botão para ativar o envio do sinal e um LED para indicar o status.

## Componentes principais

- Biblioteca Arduino-IRremote para recepção e envio de sinais IR
- Detector/demodulador IR conectado ao pino de entrada
- Botão conectado para ativar o envio do sinal IR
- LED para feedback visual do status

## Funcionalidades

- Recepção de sinais IR de múltiplos protocolos
- Armazenamento do último sinal IR recebido
- Envio do sinal IR armazenado ao pressionar o botão
- Tratamento de sinais IR desconhecidos como dados brutos

Este projeto é útil para aplicações que necessitam de controle remoto IR com capacidade de gravação e reprodução de sinais.
