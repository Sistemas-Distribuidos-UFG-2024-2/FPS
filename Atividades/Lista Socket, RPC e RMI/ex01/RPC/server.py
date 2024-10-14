from xmlrpc.server import SimpleXMLRPCServer

# Função para calcular o reajuste salarial com base no cargo
def calcular_reajuste(cargo, salario):
    if cargo == "operador":
        return salario * 1.20
    elif cargo == "programador":
        return salario * 1.18
    else:
        return salario  # Nenhum reajuste para outros cargos

# Configurar o servidor RPC
def main():
    # Iniciando o servidor na porta 65432
    server = SimpleXMLRPCServer(("localhost", 65432))
    print("Servidor RPC rodando na porta 65432...")

    # Registrar a função no servidor para que fique acessível via RPC
    server.register_function(calcular_reajuste, "calcular_reajuste")

    # Manter o servidor rodando
    server.serve_forever()

if __name__ == "__main__":
    main()
