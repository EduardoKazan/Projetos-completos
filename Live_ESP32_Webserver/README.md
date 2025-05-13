# Projeto Live ESP32 Webserver

Este projeto implementa um servidor web simples rodando em um microcontrolador ESP32, que permite controlar uma fita de LEDs RGB (NeoPixel) remotamente via navegador.

## Funcionalidades principais

- Conexão Wi-Fi para acesso ao servidor web.
- Controle de uma fita de LEDs RGB conectada ao ESP32.
- Interface web para seleção de cor via color picker e ligar/desligar os LEDs.
- Monitoramento de temperatura, umidade e pressão atmosférica (sensores integrados).
- Atualização dinâmica da página web com os valores atuais dos sensores e estado dos LEDs.

## Tecnologias e Componentes

- ESP32 como microcontrolador principal.
- Biblioteca Adafruit NeoPixel para controle dos LEDs RGB.
- Biblioteca WebServer para criação do servidor HTTP.
- Sensores de temperatura, umidade e pressão (não especificados no código, mas indicados pelas variáveis).
- Interface web simples em HTML para controle remoto.

Este projeto serve como base para aplicações IoT que necessitam de controle remoto de dispositivos e monitoramento ambiental via web.
