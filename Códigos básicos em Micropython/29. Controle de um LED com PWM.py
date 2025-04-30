from machine import Pin, PWM
import time

led = PWM(Pin(2), freq=1000)  # GPIO 2

while True:
    for duty in range(0, 1024, 10):
        led.duty(duty)
        time.sleep(0.1)
    for duty in range(1023, -1, -10):
        led .duty(duty)
        time.sleep(0.1)
