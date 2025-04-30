from machine import I2C, Pin
import time

# Inicializa o I2C
i2c = I2C(0, scl=Pin(22), sda=Pin(21))  # Ajuste os pinos SCL e SDA conforme necessário
print("\nI2C Scanner")

while True:
    devices = i2c.scan()  # Escaneia dispositivos I2C
    nDevices = len(devices)

    if nDevices == 0:
        print("Nenhum endereço I2C encontrado.")
    else:
        for address in devices:
            print("Endereço I2C encontrado: 0x{:02X}".format(address))

    print("Scan completo!")
    time.sleep(5)  # Aguarda 5 segundos antes de repetir