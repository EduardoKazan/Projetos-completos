from umqtt.simple import MQTTClient
import network
import time

ssid = 'SEU_SSID'
password = 'SUA_SENHA'

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(ssid, password)

while not wlan.isconnected():
    pass

client = MQTTClient("esp32", "broker.hivemq.com")
client.connect()

while True:
    client.publish(b"esp32/test", b"Hello MQTT")
    time.sleep(5)
