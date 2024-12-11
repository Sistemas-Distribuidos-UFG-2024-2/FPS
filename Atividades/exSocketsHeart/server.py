import socket
import time
import threading

HOST = '127.0.0.1'
PORT = 65431
DISCOVERY_PORT = 65429 

def send_heartbeat():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        while True:
            s.sendto(b"SERVER_ALIVE", ('127.0.0.1', DISCOVERY_PORT))
            time.sleep(5)

def start_server(port):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST, port))
        s.listen()
        print(f"Servidor rodando na porta {port}...")

        while True:
            conn, addr = s.accept()
            with conn:
                print(f"Conectado por {addr}")
                while True:
                    data = conn.recv(1024)
                    if not data:
                        break
                    print(f"Recebido: {data.decode()}")
                    conn.sendall(f"Servidor na porta {port}: String recebida.".encode())

if __name__ == "__main__":
    heartbeat_thread = threading.Thread(target=send_heartbeat)
    heartbeat_thread.daemon = True
    heartbeat_thread.start()

    start_server(PORT)
