import socket

HOST = '127.0.0.1'
PORT = 2150

def start_client():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST,PORT))

        date_time = s.recv(1024).decode()
        print(f"Received date and time from server: {date_time}")
    
if __name__ == "__main__":
    start_client()
