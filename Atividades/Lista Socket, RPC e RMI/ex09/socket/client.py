import socket

def obter_nome_carta(valor, naipe):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 8080))

    mensagem = f"{valor} {naipe}"
    client_socket.send(mensagem.encode())

    resposta = client_socket.recv(1024).decode()
    client_socket.close()

    return resposta

valor = int(input("Digite o valor da carta (1 a 13): "))
naipe = int(input("Digite o naipe (1=Ouros, 2=Paus, 3=Copas, 4=Espadas): "))

nome_carta = obter_nome_carta(valor, naipe)
print(f"A carta é: {nome_carta}")