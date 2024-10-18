import Pyro4

def main():
    salario_service = Pyro4.Proxy("PYRO:CalculoSalarioService@localhost:9090")

    nome = input("Digite o nome do funcionário: ")
    nivel = input("Digite o nível do funcionário (A/B/C/D): ").upper()
    salario_bruto = float(input("Digite o salário bruto: "))
    dependentes = int(input("Digite o número de dependentes: "))

    salario_liquido = salario_service.calcularSalarioLiquido(nome, nivel[0], salario_bruto, dependentes)
    print(f"Salário Líquido: {salario_liquido}")

if __name__ == "__main__":
    main()