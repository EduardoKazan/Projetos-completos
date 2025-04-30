from machine import ADC, Pin
from machine import Pin
import time

rele = Pin(2, Pin.OUT)  # GPIO 5

while True:
    rele.on()
    time.sleep(2)
    rele.off()
    time.sleep(2)