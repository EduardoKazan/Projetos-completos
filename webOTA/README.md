# Projeto ESP32 WebOTA

Este projeto implementa uma atualização Over-The-Air (OTA) para o ESP32 via interface web.

## Descrição

O sistema conecta-se a uma rede Wi-Fi e inicia um servidor web que permite a atualização do firmware do ESP32 remotamente, através de um navegador. O usuário deve fornecer uma chave de autorização para acessar a página de upload do novo firmware. Após o upload, o dispositivo realiza a atualização e reinicia automaticamente.

## Componentes principais

- ESP32 com suporte a Wi-Fi
- Servidor web embutido para interface OTA
- Biblioteca Update para gerenciamento da atualização do firmware
- Página web para autenticação e upload do firmware

## Funcionalidades

- Conexão automática à rede Wi-Fi
- Servidor web para controle da atualização OTA
- Autenticação simples via chave de autorização
- Upload e instalação do firmware via navegador
- Reinicialização automática após atualização bem-sucedida
- Mensagens de status e erro exibidas na interface web e no console serial

Este projeto é útil para facilitar a manutenção e atualização remota de dispositivos ESP32 sem necessidade de conexão física.
