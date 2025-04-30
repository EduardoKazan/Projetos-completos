from machine import ADC, Pin
import time

sensor = ADC(Pin(34))  # GPIO 34
sensor.atten(ADC.ATTN_11DB)  # Configura a atenuação

while True:
    voltage = sensor.read() * (3.3 / 4095)  # Converte a leitura para tensão
    temperature = voltage * 100  # Converte a tensão para temperatura em °C
    print('Temperatura: {:.2f}°C'.format(temperature))
    time.sleep(1)
