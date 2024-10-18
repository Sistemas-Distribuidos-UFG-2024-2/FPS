import socket

def verificar_aposentadoria(idade, tempo_servico):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('127.0.0.1', 8080))

    mensagem = f"{idade} {tempo_servico}"
    client_socket.send(mensagem.encode())

    resposta = client_socket.recv(1024).decode()
    client_socket.close()

    if resposta == '1':
        return "Pode se aposentar"
    else:
        return "Não pode se aposentar"

idade = int(input("Digite a idade: "))
tempo_servico = int(input("Digite o tempo de serviço: "))

print(verificar_aposentadoria(idade, tempo_servico))