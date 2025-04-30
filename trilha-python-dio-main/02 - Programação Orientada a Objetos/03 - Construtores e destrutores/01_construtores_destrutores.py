class Cachorro:
    def __init__(self, nome, cor, acordado=True):
        print("Inicializando a classe...")
        self.nome = nome
        self.cor = cor
        self.acordado = acordado
        if self.acordado:
            print(f"\n{self.nome} está acordado.")
        else:
            print(f"\n{self.nome} está dormindo.")
        print(f"Nome: {self.nome}")
        print(f"Cor: {self.cor}")
        print(f"Acordado: {self.acordado}")
        print("Classe inicializada com sucesso!")

    def __del__(self):
        print(f"Destruindo a classe {self.nome}...")


cao1 = Cachorro("Fred", "caramelo", True)
cao2 = Cachorro("Rex", "preto", False)
