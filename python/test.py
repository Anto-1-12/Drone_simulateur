import socket
HOST = "127.0.0.1" #local host
PORT = 5000 #port de comunication (le meme dans le cpp)

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen(1)

print("Serveur en attente...")

conn, addr = server.accept()
print("Connecté à:", addr)

run = True

while run:

    data = conn.recv(1024)
    if not data:
        break

    message = data.decode()
    print("Reçu:", message)

    response = "Reçu: " + message
    conn.sendall(response.encode())

conn.close()