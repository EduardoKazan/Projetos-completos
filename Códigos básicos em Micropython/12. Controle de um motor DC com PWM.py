from machine import Pin, PWM
import time

motor = PWM(Pin(12), freq=1000)  # GPIO 12


def set_speed(speed):
    motor.duty(speed)


while True:
    for speed in range(0, 1024, 10):
        set_speed(speed)
        time.sleep(0.1)
    for speed in range(1023, -1, -10):
        set_speed(speed)
        time.sleep(0.1)
