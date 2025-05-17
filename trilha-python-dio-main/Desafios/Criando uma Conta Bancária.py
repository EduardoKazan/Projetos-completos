# Criando uma Conta Bancária
'''
Para ler e escrever dados em Python, utilizamos as seguintes funções:
- input: lê UMA linha com dado(s) de Entrada do usuário;
- print: imprime um texto de Saída (Output), pulando linha.
'''


class ContaBancaria:
    def __init__(self, titular):
        # TODO: Inicialize a conta bancária com o nome do titular, saldo 0 e
        # liste para armazenar as operações realizadas:
        self.titular = titular
        self.saldo = 0
        self.operacoes = []

    def depositar(self, valor):
        # TODO: Implemente o método para realizar um depósito, adicione o
          valor
        # ao saldo e registre a operação:
        self.saldo += valor
        self.operacoes.append("+" + str(valor))


    def sacar(self, valor):
        # TODO: Implemente o método para realizar um saque:
        # TODO: Verifique se há saldo suficiente para o saque
        if self.saldo >= abs(valor):
            # TODO: Subtraia o valor do saldo (valor já é negativo)
            self.saldo += valor
            # TODO: Registre a operação e retorne a  mensagem de saque negado
            self.operacoes.append(str(valor))
        else:
            self.operacoes.append("Saque não permitido")


    def saldo_atual(self):
        return self.saldo


    def extrato(self):
        # TODO: Crie o método para exibir o extrato da conta e junte as
        # operações no formato correto:
        print(
            "Operações: " + ", ".join(self.operacoes)
            + "; Saldo: " + str(self.saldo)
        )


nome_titular = input().strip()
conta = ContaBancaria(nome_titular)


entrada_transacoes = input().strip()
transacoes = [int(valor) for valor in entrada_transacoes.split(",")]


for valor in transacoes:
    if valor > 0:
        conta.depositar(valor)
    else:
        conta.sacar(valor)


conta.extrato()