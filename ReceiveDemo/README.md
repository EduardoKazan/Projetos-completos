# Projeto ReceiveDemo - Arduino IR Remote

Este projeto demonstra a recepção de códigos infravermelhos (IR) utilizando a biblioteca Arduino-IRremote, além do uso da função tone() do Arduino para gerar sons.

## Descrição

O sistema detecta o pressionamento prolongado de um botão IR (repetições múltiplas de um comando) e permite a geração de tons audíveis para feedback. Um botão de depuração pode ser usado para gerar uma saída longa que pode interferir na detecção de repetições.

O projeto suporta múltiplos protocolos IR, com a possibilidade de ativar ou desativar protocolos específicos conforme necessário.

## Componentes principais

- Biblioteca Arduino-IRremote para recepção de sinais IR
- Função tone() do Arduino para geração de sons
- Botão de depuração para testes adicionais
- Suporte a múltiplos protocolos IR, incluindo LG

## Funcionalidades

- Recepção e decodificação de sinais IR
- Detecção de pressionamento prolongado de botões IR
- Geração de tons para feedback audível
- Suporte configurável a protocolos IR

Este projeto é útil para aprendizado e desenvolvimento de aplicações que envolvam controle remoto IR com feedback sonoro.
