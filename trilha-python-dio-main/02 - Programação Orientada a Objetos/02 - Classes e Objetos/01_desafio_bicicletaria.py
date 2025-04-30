class Bicicleta:
    def __init__(self, cor, modelo, ano, valor, qtd_marchas):
        self.cor = cor
        self.modelo = modelo
        self.ano = ano
        self.valor = valor
        self.qtd_marchas = qtd_marchas

    def buzinar(self):
        print("Plim plim...")

    def parar(self):
        print("Parando bicicleta...")
        print("Bicicleta parada!")

    def correr(self):
        print("Vrummmmm...")

    def __str__(self):
        return print(f"\n{self.__class__.__name__}: {', '.join([f'{chave}={valor}' for chave, valor in self.__dict__.items()])}\n")


b1 = Bicicleta("azul", "Caloi", "1999", "R$1.000,00", "5")
b1.__str__()

b2 = Bicicleta("verde", "Monark", "2005", "R$800,00", "18")
b2.__str__()
