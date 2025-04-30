from machine import ADC, Pin
import time

sensor = ADC(Pin(35))  # GPIO 35
sensor.atten(ADC.ATTN_11DB)  # Configura a atenuação

while True:
    value = sensor.read()
    print('Nível de gás:', value)
    time.sleep(1)
