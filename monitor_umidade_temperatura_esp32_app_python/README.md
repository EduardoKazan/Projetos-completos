# Monitoramento de Umidade e Temperatura com ESP32 e Aplicação Python

Este projeto consiste em um sistema de monitoramento de umidade e temperatura utilizando um microcontrolador ESP32 com sensor DHT11 e uma aplicação Python para visualização dos dados.

## Componentes do projeto

- **Firmware ESP32:** Implementa um servidor web que lê os dados do sensor DHT11 e disponibiliza via HTTP.
- **Aplicação Python:** Interface gráfica desenvolvida com PyQt5 que consulta periodicamente o servidor ESP32 para obter os dados de umidade e temperatura e exibe na tela.
- **Interface gráfica:** Arquivo `tela_monitor.ui` que define a interface da aplicação Python.
- **Imagens:** Gráficos de temperatura e umidade para visualização.

## Funcionalidades principais

- Leitura de umidade e temperatura do sensor DHT11 conectado ao ESP32.
- Servidor HTTP no ESP32 que fornece os dados do sensor.
- Aplicação Python que atualiza os dados em tempo real e exibe na interface gráfica.
- Comunicação via rede local entre ESP32 e aplicação Python.

Este projeto é ideal para quem deseja aprender a integrar sensores com microcontroladores e criar aplicações de monitoramento em tempo real utilizando Python.
