from machine import Pin
import time

led = Pin(2, Pin.OUT)  # GPIO 2

while True:
    led.on()
    time.sleep(1)
    led.off()
    time.sleep(1)
