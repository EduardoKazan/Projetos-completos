import machine
import ssd1306
import time

# Configurações do display OLED
SCREEN_WIDTH = 128
SCREEN_HEIGHT = 64
I2C_ADDRESS = 0x3C

# Inicializa o I2C e o display
i2c = machine.I2C(0, scl=machine.Pin(22), sda=machine.Pin(21))  # Ajuste os pinos conforme necessário
display = ssd1306.SSD1306_I2C(SCREEN_WIDTH, SCREEN_HEIGHT, i2c)

# Variáveis de controle do menu
selected = 0
entered = -1

# Função para exibir o menu
def display_menu():
    global selected, entered

    # Leitura dos botões
    down = machine.Pin(3, machine.Pin.IN, machine.Pin.PULL_UP)
    up = machine.Pin(2, machine.Pin.IN, machine.Pin.PULL_UP)
    enter = machine.Pin(4, machine.Pin.IN, machine.Pin.PULL_UP)
    back = machine.Pin(5, machine.Pin.IN, machine.Pin.PULL_UP)

    if not up.value():  # Botão para cima pressionado
        selected = (selected + 1) % 7  # Ciclo entre 0 e 6
        time.sleep(0.2)  # Debounce
    if not down.value():  # Botão para baixo pressionado
        selected = (selected - 1) % 7  # Ciclo entre 0 e 6
        time.sleep(0.2)  # Debounce
    if not enter.value():  # Botão de entrar pressionado
        entered = selected
    if not back.value():  # Botão de voltar pressionado
        entered = -1

    options = [
        " Menu 1",
        " Menu 2",
        " Menu 3",
        " Menu 4 ",
        " Menu 5 ",
        " Menu 6 ",
        " Menu 7 "
    ]

    display.fill(0)  # Limpa a tela
    display.text("Dsn menu test", 0, 0)
    display.text("", 0, 10)

    for i in range(7):
        if i == selected:
            display.text(options[i], 0, 20 + i * 10, 1)  # Texto selecionado
        else:
            display.text(options[i], 0, 20 + i * 10, 0)  # Texto normal

    if entered != -1:
        display.fill(0)  # Limpa a tela
        display.text("Dsn menu test", 0, 0)
        display.text(f"Menu option {entered + 1}", 0, 10)
        display.text("Dsn Menu system :)", 0, 30)

    display.show()

# Loop principal
def main():
    while True:
        display_menu()

# Executa o programa
main()