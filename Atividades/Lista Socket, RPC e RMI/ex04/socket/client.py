import socket

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 8080))

    altura = float(input("Digite a altura: "))
    sexo = input("Digite o sexo (M/F): ")

    # Envia altura e sexo ao servidor
    client_socket.send(f"{altura} {sexo}".encode())

    # Recebe o resultado do servidor
    resultado = client_socket.recv(1024).decode()
    print(f"Resposta do servidor: {resultado}")

    client_socket.close()

if __name__ == '__main__':
    main()