import Pyro4

def main():
    peso_ideal_service = Pyro4.Proxy("PYRO:PesoIdealService@localhost:9090")

    altura = float(input("Digite a altura: "))
    sexo = input("Digite o sexo (M/F): ")

    peso_ideal = peso_ideal_service.calcularPesoIdeal(altura, sexo)
    print(f"Peso ideal: {peso_ideal:.2f}")

if __name__ == "__main__":
    main()