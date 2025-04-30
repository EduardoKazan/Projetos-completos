from machine import Pin, PWM
import time

servo = PWM(Pin(13), freq=50)  # GPIO 13

def set_angle(angle):
    duty = int((angle / 180) * 102 + 26)  # Mapeia o ângulo para o valor de duty
    servo.duty(duty)

while True:
    for angle in range(0, 180, 10):
        set_angle(angle)
        time.sleep(0.5)
    for angle in range(180, 0, -10):
        set_angle(angle)
        time.sleep(0.5)