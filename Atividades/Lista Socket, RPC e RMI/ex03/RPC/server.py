from xmlrpc.server import SimpleXMLRPCServer
from xmlrpc.client import Fault
import xml.etree.ElementTree as ET

def calcular_aprovacao(n1, n2, n3):
    # Cálculo da média
    media = (n1 + n2) / 2
    if media >= 7.0:
        return "Aprovado"
    elif 3.0 < media < 7.0:
        media_final = (media + n3) / 2
        if media_final >= 5.0:
            return "Aprovado"
        else:
            return "Reprovado"
    else:
        return "Reprovado"

# Criação do servidor
server = SimpleXMLRPCServer(("localhost", 65432))
print("Servidor rodando em http://localhost:65432")

# Registra a função
server.register_function(calcular_aprovacao, "calcular_aprovacao")

# Inicia o servidor
try:
    server.serve_forever()
except KeyboardInterrupt:
    print("\nServidor encerrado.")
