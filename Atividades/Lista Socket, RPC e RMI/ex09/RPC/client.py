import Pyro4

@Pyro4.expose
class Baralho:
    def obter_nome_carta(self, valor, naipe):
        valores = ["Ás", "Dois", "Três", "Quatro", "Cinco", "Seis", "Sete", "Oito", "Nove", "Dez", "Valete", "Dama", "Rei"]
        naipes = ["Ouros", "Paus", "Copas", "Espadas"]
        return f"{valores[valor - 1]} de {naipes[naipe - 1]}"

def main():
    uri = input("Digite o URI do servidor: ").strip()
    baralho = Pyro4.Proxy(uri)

    valor = int(input("Digite o valor da carta (1 a 13): "))
    naipe = int(input("Digite o naipe (1=Ouros, 2=Paus, 3=Copas, 4=Espadas): "))

    nome_carta = baralho.obter_nome_carta(valor, naipe)
    print(f"A carta é: {nome_carta}")

if __name__ == "__main__":
    main()