from machine import I2C, Pin
import time

i2c = I2C(0, scl=Pin(22), sda=Pin(21))  # GPIO 22 (SCL), GPIO 21 (SDA)
address = 0x23  # Endereço do BH1750


def read_light():
    data = i2c.readfrom(address, 2)
    return (data[0] << 8) | data[1]


while True:
    light = read_light()
    print('Lumens:', light)
    time.sleep(1)
