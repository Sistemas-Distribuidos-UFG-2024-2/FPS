import Pyro4

@Pyro4.expose
class Banco:
    def calcular_credito(self, saldo_medio):
        if saldo_medio >= 0 and saldo_medio <= 200:
            return 0
        elif saldo_medio >= 201 and saldo_medio <= 400:
            return saldo_medio * 0.20
        elif saldo_medio >= 401 and saldo_medio <= 600:
            return saldo_medio * 0.30
        else:
            return saldo_medio * 0.40

def main():
    uri = input("Digite o URI do servidor: ").strip()
    banco = Pyro4.Proxy(uri)

    saldo_medio = float(input("Digite o saldo médio: "))

    credito = banco.calcular_credito(saldo_medio)
    print(f"Saldo médio: {saldo_medio}, Crédito concedido: {credito}")

if __name__ == "__main__":
    main()