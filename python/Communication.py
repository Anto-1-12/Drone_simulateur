"""""
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
"""""
import json

def InitialisationConnection():
    import socket
    HOST = "127.0.0.1" #local host
    PORT = 5000 #port de comunication (le meme dans le cpp)

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(1)

    print("Serveur en attente...")
    global conn
    conn, addr = server.accept()
    print("Connecté à:", addr)
    #fcntl( sock, F_SETFL, O_NONBLOCK)
    #socket.fcntl( server, socket.F_SETFL, socket.O_NONBLOCK)
    conn.setblocking(False)


def Canalouvert():
    try :
        data = conn.recv(1024)
        if data :
            message = data.decode()
            print("Reçu:", message)
            # raw = aide IA
            """
            {"a": 1, "b": 2}
            {"a": 3, "b": 4}
            """
            liste = [json.loads(line) for line in message.splitlines() if line.strip()]
            #test=json.loads(message)
            return liste
    except:
        print('RAS')

def Transmission(message):
    conn.sendall(message.encode())

def FermetureCanal():
    conn.close()
    print("Fermeture du Canal de transmission")