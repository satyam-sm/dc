import socket
import threading
from datetime import datetime

HOST = '127.0.0.1'
PORT = 2150

def handle_client(conn,addr):
    with conn:
        print(f"Accepted connection from {addr}")
        current_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        conn.send(current_time.encode())

def start_server():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST,PORT))
        s.listen()
        print(f"Date-Time Server started and listening on port {PORT}")

        while True:
            conn, addr = s.accept()       
            thread = threading.Thread(target=handle_client, args=(conn,addr))
            thread.start()

if __name__ == "__main__":
    start_server()
