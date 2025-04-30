from machine import Pin, time_pulse_us
import time

trigger = Pin(12, Pin.OUT)  # GPIO 12
echo = Pin(14, Pin.IN)  # GPIO 14


def get_distance():
    trigger.on()
    time.sleep_us(10)
    trigger.off()
    duration = time_pulse_us(echo, 1)
    distance = (duration * 0.0343) / 2  # Calcula a distância em cm
    return distance


while True:
    distance = get_distance()
    print('Distância:', distance, 'cm')
    time.sleep(1)
