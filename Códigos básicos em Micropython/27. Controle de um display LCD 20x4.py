import machine
import time
from machine import I2C
import lcd

# GPIO 22 (SCL), GPIO 21 (SDA)
i2c = I2C(0, scl=machine.Pin(22), sda=machine.Pin(21))
lcd = lcd.LCD(i2c, 20, 4)

lcd.clear()
lcd.putstr("Olá, ESP32!")
time.sleep(2)
lcd.clear()
lcd.putstr("MicroPython")
