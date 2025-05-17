# Registro de Transações Bancárias
def calcular_saldo(transacoes):
    saldo = 0

    # Itera sobre cada transação na lista:
    for transacao in transacoes:
        # Adiciona o valor da transação ao saldo
        saldo += transacao

    # Retorna o saldo formatado em moeda brasileira com duas casas decimais:
    return f"Saldo: R$ {saldo:.2f}"


entrada_usuario = input()
entrada_usuario = entrada_usuario.strip("[]").replace(" ", "")
transacoes = [float(valor)
              for valor in entrada_usuario.split(",") if valor != ""]

# Calcula o saldo com base nas transações informadas:
resultado = calcular_saldo(transacoes)

print(resultado)
