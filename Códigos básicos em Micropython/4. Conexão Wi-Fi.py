import network

ssid = 'CLARO_2G9F971E'
password = 'WrZHU48hzz'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

while not wlan.isconnected():
    pass

print('Conectado, IP:', wlan.ifconfig()[0])
