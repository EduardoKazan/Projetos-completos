import urequests
import network
import time

ssid = 'SEU_SSID'
password = 'SUA_SENHA'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

while not wlan.isconnected():
    pass

print('Conectado, IP:', wlan.ifconfig()[0])

while True:
    response = urequests.post('http://example.com/api',
                              json={'data': 'Hello, World!'})
    print('Status:', response.status_code)
    response.close()
    time.sleep(10)
