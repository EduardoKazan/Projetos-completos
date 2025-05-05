from machine import Pin
from time import sleep
import dht

# Substitua 14 pelo número do pino GPIO que você está usando
sensor = dht.DHT11(Pin(14))

while True:
    try:
        sensor.measure()
        temp = sensor.temperature()
        umid = sensor.humidity()
        print(f"Temperatura: {temp}°C | Umidade: {umid}%")
    except OSError as e:
        print("Erro na leitura do sensor:", e)
    sleep(2)  # Aguarda 2 segundos antes da próxima leitura
