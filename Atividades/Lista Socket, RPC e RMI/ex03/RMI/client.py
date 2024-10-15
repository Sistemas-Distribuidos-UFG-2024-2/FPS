import Pyro4

def main():
    # Conectar ao servidor
    uri = "PYRONAME:AprovacaoService"  # Nome do serviço que você registrou
    aprovacao_service = Pyro4.Proxy(uri)

    # Ler notas do usuário
    n1 = float(input("Digite a primeira nota (N1): "))
    n2 = float(input("Digite a segunda nota (N2): "))
    n3 = float(input("Digite a terceira nota (N3): "))

    # Chamar o método remoto
    resultado = aprovacao_service.calcularAprovacao(n1, n2, n3)
    print("Resultado:", resultado)

if __name__ == "__main__":
    main()
