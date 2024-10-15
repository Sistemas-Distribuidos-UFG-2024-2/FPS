from xmlrpc.server import SimpleXMLRPCServer

def verificar_maioridade(nome, sexo, idade):
    if sexo.lower() == "masculino" and idade >= 18:
        return f"{nome} atingiu a maioridade."
    elif sexo.lower() == "feminino" and idade >= 21:
        return f"{nome} atingiu a maioridade."
    else:
        return f"{nome} não atingiu a maioridade."

# Cria o servidor na porta 8000
server = SimpleXMLRPCServer(("localhost", 8000))
print("Servidor de RPC rodando na porta 8000...")

# Registra a função
server.register_function(verificar_maioridade, "verificar_maioridade")

# Mantém o servidor rodando
server.serve_forever()