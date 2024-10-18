import socket

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 8080))

    idade = int(input("Digite a idade do nadador: "))

    # Envia a idade ao servidor
    client_socket.send(f"{idade}".encode())

    # Recebe a classificação do servidor
    classificacao = client_socket.recv(1024).decode()
    print(f"Classificação: {classificacao}")

    client_socket.close()

if __name__ == '__main__':
    main()