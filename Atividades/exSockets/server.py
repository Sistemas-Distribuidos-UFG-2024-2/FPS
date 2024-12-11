import socket

HOST = '127.0.0.1' 
PORT = 65432        

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen()
    print("Servidor esperando conexão...")

    conn, addr = s.accept()
    with conn:
        print(f"Conectado por {addr}")
        while True:
            # Recebe dados do cliente
            data = conn.recv(1024)
            if not data:
                break
            print(f"Recebido: {data.decode()}")
            
            # Envia uma resposta de volta
            conn.sendall(b'String recebida pelo servidor Python.')
