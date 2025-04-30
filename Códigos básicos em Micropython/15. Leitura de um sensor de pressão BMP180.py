import machine
import bmp180
import time

i2c = machine.I2C(0, scl=machine.Pin(22), sda=machine.Pin(21)
                  )  # GPIO 22 (SCL), GPIO 21 (SDA)
sensor = bmp180.BMP180(i2c)

while True:
    temperature = sensor.temperature
    pressure = sensor.pressure
    print('Temperatura: {}°C, Pressão: {} hPa'.format(temperature, pressure))
    time.sleep(2)
