from machine import ADC, Pin
import time

ldr = ADC(Pin(34))  # GPIO 34
ldr.atten(ADC.ATTN_11DB)  # Configura a atenuação

while True:
    value = ldr.read()
    print('Valor LDR:', value)
    time.sleep(1)
