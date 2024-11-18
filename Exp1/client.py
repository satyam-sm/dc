import socket
HOST = '127.0.0.1'
PORT = 65432
def start_client():
    """Function to start the client."""
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        print(f"Connected to the remote server at {HOST}:{PORT}")
        while True:
            message = input("Todays message: ")
            if message.lower() == 'exit':
                break
            s.sendall(message.encode())
            data = s.recv(1024)
            print(f"Echo from the remote server: {data.decode()}")

if __name__ == "__main__":
    start_client()
