from machine import ADC, Pin
import time

sensor = ADC(Pin(34))  # GPIO 34
sensor.atten(ADC.ATTN_11DB)  # Configura a atenuação

while True:
    value = sensor.read()
    print('Umidade do solo:', value)
    time.sleep(1)
