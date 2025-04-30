from faker import Faker

# Criando uma instância do Faker
fake = Faker('pt_BR')

# Gerando dados ficticios
print("Nome:", fake.name())
print("Endereço:", fake.address())
print("Telefone:", fake.phone_number())
print("Email:", fake.email())
print("Data de Nascimento:",
      fake.date_of_birth(minimum_age=18, maximum_age=65))
print("Profissão:", fake.job())
print("Texto:", fake.text())
