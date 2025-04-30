from machine import Pin
import time

rele = Pin(5, Pin.OUT)  # GPIO 5
button = Pin(0, Pin.IN)  # GPIO 0

while True:
    if button.value() == 1:
        rele.on()
    else:
        rele.off()
    time.sleep(0.1)
