# Projeto Weather Logger

Este projeto implementa um sistema de monitoramento de temperatura e umidade utilizando um sensor DHT11, com envio dos dados para um servidor MQTT.

## Descrição

O sistema conecta-se a uma rede Wi-Fi e publica leituras de temperatura e umidade em tópicos MQTT específicos. Utiliza o sensor DHT11 para capturar os dados ambientais e o protocolo MQTT para comunicação com servidores de mensagens, permitindo monitoramento remoto.

## Componentes principais

- Sensor DHT11 para medição de temperatura e umidade
- Módulo Wi-Fi para conexão à internet
- Biblioteca PubSubClient para comunicação MQTT
- Servidor MQTT público (test.mosquitto.org)

## Funcionalidades

- Conexão automática à rede Wi-Fi
- Leitura contínua dos dados de temperatura e umidade
- Publicação dos dados em tópicos MQTT para consumo por outros dispositivos ou aplicações
- Reconexão automática ao servidor MQTT em caso de perda de conexão
- Monitoramento via console serial para depuração

Este projeto é útil para aplicações de monitoramento ambiental com integração IoT via MQTT.
