import Pyro4

def main():
    classificacao_service = Pyro4.Proxy("PYRO:ClassificacaoNadadorService@localhost:9090")

    idade = int(input("Digite a idade do nadador: "))

    classificacao = classificacao_service.classificarNadador(idade)
    print(f"Classificação: {classificacao}")

if __name__ == "__main__":
    main()