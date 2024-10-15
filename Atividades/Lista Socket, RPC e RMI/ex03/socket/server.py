import socket

def calcular_aprovacao(n1, n2, n3):
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

def main():
    # Cria um socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    # Define o endereço e a porta
    server_address = ('localhost', 65432)
    server_socket.bind(server_address)

    # Escuta por conexões
    server_socket.listen(1)
    print("Aguardando conexão do cliente...")

    while True:
        # Aceita uma conexão
        client_socket, client_address = server_socket.accept()
        print(f"Conexão de {client_address}")

        try:
            # Recebe os dados do cliente
            data = client_socket.recv(1024).decode()
            notas = list(map(float, data.split(',')))  # Converte as notas em float

            # Verifica se três notas foram recebidas
            if len(notas) == 3:
                n1, n2, n3 = notas
                resultado = calcular_aprovacao(n1, n2, n3)
                client_socket.sendall(resultado.encode())
            else:
                client_socket.sendall("Erro: Precisamos de 3 notas.".encode())

        finally:
            client_socket.close()

if __name__ == "__main__":
    main()
