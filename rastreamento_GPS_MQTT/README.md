# Projeto de Rastreamento GPS com MQTT

Este projeto é uma adaptação do canal "INTERNET E COISAS" e implementa um sistema de rastreamento via GPS utilizando MQTT para comunicação.

## Descrição

O sistema utiliza um módulo GPS para obter a localização (latitude, longitude), além de informações como HDOP e idade dos dados. Esses dados são publicados em tópicos MQTT específicos para serem consumidos por outros dispositivos ou sistemas.

A comunicação MQTT é feita com um broker seguro, e o dispositivo conecta-se via Wi-Fi para enviar as informações.

## Componentes principais

- Módulo GPS para obtenção de dados de localização e tempo
- Conexão Wi-Fi para acesso à rede
- Cliente MQTT para publicação dos dados em tópicos específicos
- Biblioteca TinyGPS++ para interpretação dos dados GPS
- Biblioteca PubSubClient para comunicação MQTT

## Funcionalidades

- Conexão automática à rede Wi-Fi
- Leitura contínua dos dados do GPS
- Publicação dos dados de latitude, longitude, HDOP, idade dos dados e timestamp via MQTT
- Atualização periódica dos dados a cada 60 segundos

Este projeto serve como base para aplicações de rastreamento e monitoramento remoto utilizando GPS e MQTT em microcontroladores ESP32.
