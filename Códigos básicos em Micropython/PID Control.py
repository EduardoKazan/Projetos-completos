from machine import ADC, Pin, PWM
import time

class PID:
    def __init__(self, kP, kI, kD):
        self.kP = kP
        self.kI = kI
        self.kD = kD
        self.error = 0
        self.sample = 0
        self.lastSample = 0
        self.P = 0
        self.I = 0
        self.D = 0
        self.pid = 0
        self.setPoint = 0
        self.lastProcess = -1

    def add_new_sample(self, sample):
        self.sample = sample

    def set_set_point(self, setPoint):
        self.setPoint = setPoint

    def process(self):
        if self.lastProcess == -1:
            self.lastSample = self.sample
            self.lastProcess = time.ticks_ms()

        # Implementação PID
        self.error = self.setPoint - self.sample
        current_time = time.ticks_ms()
        deltaTime = (current_time - self.lastProcess) / 1000.0
        self.lastProcess = current_time

        # Verifica se deltaTime é zero
        if deltaTime <= 0:
            return self.pid  # Retorna o valor atual do PID sem calcular

        # P
        self.P = self.error * self.kP

        # I
        self.I += (self.error * self.kI) * deltaTime

        # D
        self.D = (self.lastSample - self.sample) * self.kD / deltaTime
        self.lastSample = self.sample

        # Soma tudo
        self.pid = self.P + self.I + self.D

        return self.pid

# Configuração dos pinos
pSENSOR = ADC(Pin(34))  # Exemplo de pino ADC válido no ESP32
pCONTROLE = PWM(Pin(25))  # Exemplo de pino PWM válido no ESP32

# Inicialização do PID
meuPid = PID(1.0, 0, 0)

# Configuração inicial
pSENSOR.atten(ADC.ATTN_11DB)  # Configura a atenuação para ler até 3.6V

while True:
    # Lê temperatura
    temperature = int((pSENSOR.read() / 4095) * 100)  # Para ESP32, a leitura ADC vai até 4095

    # Manda pro objeto PID!
    meuPid.add_new_sample(temperature)

    # Converte para controle
    controlePwm = int(meuPid.process() + 50)

    # Saída do controle
    pCONTROLE.duty(controlePwm)

    time.sleep(0.1)  # Delay para evitar leitura excessiva