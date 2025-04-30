
menu = """
========== Sistema Bancario ==========
            [1] Extrato
            [2] Depositar
            [3] Sacar
            [4] Sair
======================================
"""

saldo = 0
LIMITE = 500
extrato = []
numero_saques = 0
LIMITE_SAQUES = 3


def depositar(saldo, extrato):
    valor = float(input("Digite o valor para depósito: "))
    print(f"Você escolheu depositar R$ {valor}")
    if valor > 0:
        saldo += valor
        extrato.append(f"Depósito: R$ {valor:.2f}")
    else:
        print("Operação falhou! O valor informado é inválido.")
    return saldo, extrato


def sacar(saldo, extrato, numero_saques):
    valor = float(input("Digite o valor para saque: "))
    print(f"Você escolheu sacar R$ {valor}")
    excedeu_saldo = valor > saldo
    excedeu_limite = valor > LIMITE
    excedeu_saques = numero_saques >= LIMITE_SAQUES

    if excedeu_saldo:
        print("Operação falhou! Você não tem saldo suficiente.")
    elif excedeu_limite:
        print("Operação falhou! O valor do saque excede o limite.")
    elif excedeu_saques:
        print("Operação falhou! Número máximo de saques excedido.")
    elif valor > 0:
        saldo -= valor
        extrato.append(f"Saque: R$ {valor:.2f}")
        numero_saques += 1
    else:
        print("Operação falhou! O valor informado é inválido.")

    return saldo, extrato, numero_saques


def ver_extrato(saldo, extrato):
    print("Você escolheu: EXTRATO")
    print("\n================ EXTRATO ================")
    if not extrato:
        print("Não foram realizadas movimentações.")
    else:
        print("\n".join(extrato))
    print(f"\nSaldo: R$ {saldo:.2f}")
    print("==========================================")
    return saldo, extrato


def sair():
    print("Saindo do sistema. Até logo!")


while True:
    print(menu)

    opcao = input("Escolha uma opção: ")

    if opcao == "1":
        ver_extrato(saldo, extrato)
    elif opcao == "2":
        saldo, extrato = depositar(saldo, extrato)
    elif opcao == "3":
        sacar(saldo, extrato, numero_saques)
    elif opcao == "4":
        sair()
        break
    else:
        print("Opção inválida. Tente novamente.")
# end while


"""NOVAS FUNCIONALIDADES:

- Estabelecer um limite de 10 transações diárias para uma conta
- Se o usuário tentar fazer uma transação após atingir o limite,
deve ser informado que ele excedeu o número de transações permitidas
para aquele dia.
- Mostre no extrato, a data e hora de todas as transações.
"""
