from machine import Pin, PWM
import time

red = PWM(Pin(25), freq=1000)  # GPIO 25
green = PWM(Pin(26), freq=1000)  # GPIO 26
blue = PWM(Pin(27), freq=1000)  # GPIO 27


def set_color(r, g, b):
    red.duty(r)
    green.duty(g)
    blue.duty(b)


while True:
    set_color(1023, 0, 0)  # Vermelho
    time.sleep(1)
    set_color(0, 1023, 0)  # Verde
    time.sleep(1)
    set_color(0, 0, 1023)  # Azul
    time.sleep(1)
