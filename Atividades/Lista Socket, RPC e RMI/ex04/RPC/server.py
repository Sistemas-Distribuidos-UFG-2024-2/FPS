from xmlrpc.server import SimpleXMLRPCServer

def calcular_peso_ideal(altura, sexo):
    if sexo == 'M':
        return (72.7 * altura) - 58
    else:
        return (62.1 * altura) - 44.7

def main():
    server = SimpleXMLRPCServer(("localhost", 8000))
    print("Servidor RPC rodando na porta 8000...")
    server.register_function(calcular_peso_ideal, "calcular_peso_ideal")
    server.serve_forever()

if __name__ == '__main__':
    main()