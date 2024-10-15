import socket

def verifica_maioridade(nome, sexo, idade):
    if sexo == 'M':
        if idade >= 18:
            return f"{nome} já atingiu a maioridade."
        else:
            return f"{nome} não atingiu a maioridade."
    elif sexo == 'F':
        if idade >= 21:
            return f"{nome} já atingiu a maioridade."
        else:
            return f"{nome} não atingiu a maioridade."
    else:
        return "Sexo inválido."

def servidor():
    # Configuração do socket do servidor
    host = '127.0.0.1'
    porta = 65432

    # Criando o socket TCP
    servidor_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    servidor_socket.bind((host, porta))

    # O servidor vai começar a escutar por conexões
    servidor_socket.listen()

    print(f"Servidor ouvindo na porta {porta}...")

    while True:
        # Aceitando conexão do cliente
        conn, addr = servidor_socket.accept()
        print(f"Conectado por {addr}")

        # Recebendo dados do cliente
        data = conn.recv(1024).decode()
        if not data:
            break

        # Os dados recebidos estarão no formato "nome,sexo,idade"
        nome, sexo, idade = data.split(',')
        idade = int(idade)

        # Verificando maioridade
        resultado = verifica_maioridade(nome, sexo, idade)

        # Enviando resposta ao cliente
        conn.sendall(resultado.encode())

        # Fechando conexão com o cliente
        conn.close()

if __name__ == "__main__":
    servidor()
