from xmlrpc.server import SimpleXMLRPCServer

def calcular_salario_liquido(nivel, salario_bruto, dependentes):
    descontos = {
        "A": (0.03, 0.08),
        "B": (0.05, 0.10),
        "C": (0.08, 0.15),
        "D": (0.10, 0.17)
    }
    
    desconto = descontos.get(nivel.upper())
    if desconto:
        taxa_desconto = desconto[1] if dependentes > 0 else desconto[0]
        return salario_bruto - (salario_bruto * taxa_desconto)
    return -1  # Nível inválido

def main():
    server = SimpleXMLRPCServer(("localhost", 8000))
    print("Servidor RPC rodando na porta 8000...")
    server.register_function(calcular_salario_liquido, "calcular_salario_liquido")
    server.serve_forever()

if __name__ == '__main__':
    main()