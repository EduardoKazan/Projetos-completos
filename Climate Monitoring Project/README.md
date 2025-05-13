# Projeto de Monitoramento Climático com ESP32 e MQTT

Este projeto consiste em uma estação meteorológica baseada no microcontrolador ESP32, que utiliza diversos sensores para monitorar parâmetros ambientais como temperatura, umidade, pressão atmosférica, luminosidade, índice UV e detecção de chuva.

## Principais características

- Utiliza sensores AHT21, CCS811, BMP180, TSL2561, sensor UV GUVA-S12S e sensor de chuva analógico e digital.
- Comunicação via Wi-Fi com envio dos dados para um broker MQTT seguro utilizando SSL.
- Display OLED SSD1306 para exibição local dos dados dos sensores.
- Alternância entre diferentes telas de sensores através de um botão físico.
- Código modular e configurável para fácil adaptação a diferentes projetos de monitoramento ambiental.

## Aplicações

Este projeto é ideal para quem deseja montar uma estação meteorológica compacta e conectada, com capacidade de monitoramento remoto via MQTT, podendo ser utilizado em projetos de automação residencial, agricultura de precisão, pesquisa ambiental e IoT.
