import machine
import ssd1306
import time

i2c = machine.I2C(0, scl=machine.Pin(22), sda=machine.Pin(21)
                  )  # GPIO 22 (SCL), GPIO 21 (SDA)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)

while True:
    oled.fill(0)  # Limpa a tela
    oled.text('Olá, ESP32!', 0, 0)
    oled.show()
    time.sleep(1)
