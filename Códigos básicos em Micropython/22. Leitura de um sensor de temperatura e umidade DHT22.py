import dht
from machine import Pin
import time

sensor = dht.DHT22(Pin(4))  # GPIO 4

while True:
    sensor.measure()
    temp = sensor.temperature()
    humidity = sensor.humidity()
    print('Temperatura: {}°C, Umidade: {}%'.format(temp, humidity))
    time.sleep(2)
