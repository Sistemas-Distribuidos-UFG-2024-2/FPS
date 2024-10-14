import Pyro5.api

@Pyro5.api.expose
class ReajusteService:
    def calcular_reajuste(self, nome, cargo, salario):
        if cargo == "operador":
            return salario * 1.20
        elif cargo == "programador":
            return salario * 1.18
        else:
            return salario

def main():
    Pyro5.api.start_server(ReajusteService, host="localhost", port=9090)

if __name__ == "__main__":
    main()