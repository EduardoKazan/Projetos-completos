from machine import Pin
import time

button = Pin(0, Pin.IN)  # GPIO 0

while True:
    if button.value() == 1:
        print("Botão pressionado!")
    time.sleep(0.1)
