import Pyro4

# Conectando ao servidor RMI
uri = "PYRONAME:Maioridade"
maioridade = Pyro4.Proxy(uri)

# Lendo os dados do usuário
nome = input("Digite o seu nome: ")
sexo = input("Digite o seu sexo (masculino/feminino): ")
idade = int(input("Digite a sua idade: "))

# Verificando a maioridade
resultado = maioridade.verificarMaioridade(nome, sexo, idade)
print(resultado)
