from machine import Pin
import time
step_pin = Pin(14, Pin.OUT)  # GPIO 14
dir_pin = Pin(27, Pin.OUT)  # GPIO 27


def step_motor(steps, direction):
    dir_pin.value(direction)
    for _ in range(steps):
        step_pin.on()
        time.sleep(0.001)
        step_pin.off()
        time.sleep(0.001)


while True:
    step_motor(200, 1)  # Gira no sentido horário
    time.sleep(1)
    step_motor(200, 0)  # Gira no sentido anti-horário
    time.sleep(1)
