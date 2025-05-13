# Projeto Tago Basic MPU

Este projeto utiliza um sensor MPU6050 para capturar dados de aceleração e giroscópio, enviando-os para a nuvem TagoIO via conexão Wi-Fi.

## Descrição

O sistema conecta-se a uma rede Wi-Fi e ao serviço TagoIO para enviar dados em tempo real do sensor MPU6050, que mede aceleração e rotação em três eixos (X, Y, Z). Os dados são lidos continuamente e enviados para a plataforma para monitoramento remoto.

## Componentes principais

- Sensor MPU6050 (acelerômetro e giroscópio)
- Módulo Wi-Fi para conexão à internet
- Biblioteca Tago para comunicação com a plataforma TagoIO
- Comunicação I2C para interface com o sensor MPU6050

## Funcionalidades

- Conexão automática à rede Wi-Fi
- Leitura contínua dos dados do acelerômetro e giroscópio
- Envio dos dados para a plataforma TagoIO para visualização e análise remota
- Monitoramento via console serial para depuração

Este projeto é útil para aplicações de monitoramento de movimento e orientação com envio de dados para a nuvem.
