import Pyro4

@Pyro4.expose
class Aposentadoria:
    def verificar(self, idade, tempo_servico):
        if idade >= 65 or (idade >= 60 and tempo_servico >= 25) or tempo_servico >= 30:
            return 1
        return 0

def main():
    uri = input("Digite o URI do servidor: ").strip()
    aposentadoria = Pyro4.Proxy(uri)

    idade = int(input("Digite a idade: "))
    tempo_servico = int(input("Digite o tempo de serviço: "))

    if aposentadoria.verificar(idade, tempo_servico) == 1:
        print("Pode se aposentar")
    else:
        print("Não pode se aposentar")

if __name__ == "__main__":
    main()