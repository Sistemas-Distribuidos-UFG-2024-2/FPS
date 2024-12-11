import socket
import itertools
import threading
import time

active_servers = []
server_lock = threading.Lock()

def discovery_service():
    discovery_port = 65429

    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind(('127.0.0.1', discovery_port))
        print("Serviço de descoberta aguardando heartbeats...")

        while True:
            # Recebe o heartbeat de um servidor
            data, addr = s.recvfrom(1024)
            if data == b"SERVER_ALIVE":
                with server_lock:
                    if addr not in active_servers:
                        active_servers.append(addr)
                        print(f"Novo servidor descoberto: {addr}")

def forward_to_server(data):
    with server_lock:
        if not active_servers:
            return b"Erro: Nenhum servidor disponivel."

        # Seleciona o próximo servidor de forma round-robin
        server = next(itertools.cycle(active_servers))
    
    print(f"Encaminhando para o servidor: {server}")

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect(server)
        s.sendall(data)
        response = s.recv(1024)
        return response

def start_middleware():
    """Inicia o middleware que gerencia as requisições dos clientes."""
    HOST = '127.0.0.1'
    PORT = 65430

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, PORT))
        s.listen()
        print("Middleware aguardando conexões dos clientes...")

        while True:
            conn, addr = s.accept()
            with conn:
                print(f"Conectado com cliente: {addr}")
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    print(f"Recebido do cliente: {data.decode()}")

                    response = forward_to_server(data)

                    conn.sendall(response)

if __name__ == "__main__":
    discovery_thread = threading.Thread(target=discovery_service)
    discovery_thread.daemon = True
    discovery_thread.start()

    start_middleware()
