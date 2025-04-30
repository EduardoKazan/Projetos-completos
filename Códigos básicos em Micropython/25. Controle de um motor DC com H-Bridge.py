from machine import Pin
import time

in1 = Pin(12, Pin.OUT)  # GPIO 12
in2 = Pin(13, Pin.OUT)  # GPIO 13

def motor_forward():
    in1.on()
    in2.off()

def motor_backward():
    in1.off()
    in2.on()

while True:
    motor_forward()
    time.sleep(2)
    motor_backward()
    time.sleep(2)