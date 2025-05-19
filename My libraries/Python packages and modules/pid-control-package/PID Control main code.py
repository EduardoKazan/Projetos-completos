import pid_control
import machine
import time

# Configuração dos pinos
pSENSOR = ADC(Pin(34))  # Exemplo de pino ADC válido no ESP32
pCONTROLE = PWM(Pin(25))  # Exemplo de pino PWM válido no ESP32

# Inicialização do PID
meuPid = PIDController(1.0, 0, 0)

# Configuração inicial
pSENSOR.atten(ADC.ATTN_11DB)  # Configura a atenuação para ler até 3.6V

while True:
    # Lê temperatura
    # Para ESP32, a leitura ADC vai até 4095
    temperature = int((pSENSOR.read() / 4095) * 100)

    # Manda pro objeto PID!
    meuPid.add_new_sample(temperature)

    # Converte para controle
    controlePwm = int(meuPid.process() + 50)

    # Saída do controle
    pCONTROLE.duty(controlePwm)

    time.sleep(0.1)  # Delay para evitar leitura excessiva
