import socket

# Definir o endereço IP e a porta para a comunicação com o servidor
HOST = '127.0.0.1'  # Localhost
PORT = 65432        # Porta para o servidor

# Função para enviar os dados e receber a resposta do servidor
def main():
    # Criação do socket
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        # Conectar ao servidor
        s.connect((HOST, PORT))
        
        # Solicitar informações ao usuário
        nome = input("Digite o nome do funcionário: ")
        cargo = input("Digite o cargo (operador ou programador): ")
        salario = input("Digite o salário do funcionário: ")
        
        # Enviar dados concatenados para o servidor
        dados = f"{nome},{cargo},{salario}"
        s.sendall(dados.encode())
        
        # Receber o resultado do servidor
        resposta = s.recv(1024)
        print("Resposta do servidor:", resposta.decode())

if __name__ == "__main__":
    main()
