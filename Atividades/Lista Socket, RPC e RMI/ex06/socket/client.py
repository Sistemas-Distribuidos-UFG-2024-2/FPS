import socket

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 8080))

    nome = input("Digite o nome do funcionário: ")
    nivel = input("Digite o nível do funcionário (A/B/C/D): ").upper()
    salario_bruto = float(input("Digite o salário bruto: "))
    dependentes = int(input("Digite o número de dependentes: "))

    # Envia os dados ao servidor
    client_socket.send(f"{nome} {nivel} {salario_bruto} {dependentes}".encode())

    # Recebe o resultado do servidor
    resposta = client_socket.recv(1024).decode()
    print(resposta)

    client_socket.close()

if __name__ == '__main__':
    main()