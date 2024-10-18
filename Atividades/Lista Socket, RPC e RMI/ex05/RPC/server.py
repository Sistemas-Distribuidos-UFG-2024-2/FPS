from xmlrpc.server import SimpleXMLRPCServer

def classificar_nadador(idade):
    if 5 <= idade <= 7:
        return "Infantil A (5-7 anos)"
    elif 8 <= idade <= 10:
        return "Infantil B (8-10 anos)"
    elif 11 <= idade <= 13:
        return "Juvenil A (11-13 anos)"
    elif 14 <= idade <= 17:
        return "Juvenil B (14-17 anos)"
    elif idade >= 18:
        return "Adulto (maiores de 18 anos)"
    else:
        return "Sem categoria (menos de 5 anos)"

def main():
    server = SimpleXMLRPCServer(("localhost", 8000))
    print("Servidor RPC rodando na porta 8000...")
    server.register_function(classificar_nadador, "classificar_nadador")
    server.serve_forever()

if __name__ == '__main__':
    main()