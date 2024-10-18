import socket

def calcular_credito(saldo_medio):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 8080))

    mensagem = f"{saldo_medio}"
    client_socket.send(mensagem.encode())

    resposta = client_socket.recv(1024).decode()
    client_socket.close()

    return float(resposta)

saldo_medio = float(input("Digite o saldo médio: "))
credito = calcular_credito(saldo_medio)
print(f"Saldo médio: {saldo_medio}, Crédito concedido: {credito}")