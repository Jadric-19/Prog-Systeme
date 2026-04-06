import socket
import sys
import os

HOST = "127.0.0.1"
PORT = 12345

if len(sys.argv) != 2:
    print("Usage: python client.py fichier.txt")
    exit()

file_path = sys.argv[1]

s = socket.socket()
s.connect((HOST, PORT))

# envoyer nom fichier
nom = os.path.basename(file_path)
s.send(nom.encode())

# envoyer contenu
f = open(file_path, "rb")

while True:
    data = f.read(1024)
    if not data:
        break
    s.send(data)

f.close()
s.close()

print("Fichier envoye !")