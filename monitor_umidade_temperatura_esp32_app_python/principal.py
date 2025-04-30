from PyQt5 import uic, QtWidgets
import requests
import time
import threading
import socket


def obter_ip_local():
    try:
        # Cria um socket UDP
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        # Conecta a um endereço IP externo (não precisa ser acessível)
        s.connect(("8.8.8.8", 80))  # Usando o Google DNS
        ip_local = s.getsockname()[0]  # Obtém o IP local
    finally:
        s.close()  # Fecha o socket
    return ip_local


if __name__ == "__main__":
    ip = obter_ip_local()
    print(f"Seu IP local é: {ip}")


def atualiza_dados():
    esp32_ip = "192.168.x.x"  # Substitua pelo IP do ESP32
    while True:
        time.sleep(2)
        try:
            # Verifique se este IP está correto
            resposta = requests.get(esp32_ip)
            dados = resposta.text
            print("Dados recebidos:", dados)  # Para depuração
            dados_separados = dados.split("e")
            if len(dados_separados) == 2:  # Verifica se os dados estão no formato esperado
                tela.label_6.setText(dados_separados[1][0:4] + "°C")
                tela.label_7.setText(dados_separados[0][0:4] + "%")
            else:
                print("Formato de dados inesperado:", dados_separados)
        except Exception as e:
            print("Erro ao fazer requisição:", e)  # Captura erros


app = QtWidgets.QApplication([])
tela = uic.loadUi("tela_monitor.ui")
threading.Thread(target=atualiza_dados).start()
tela.show()
app.exec()
