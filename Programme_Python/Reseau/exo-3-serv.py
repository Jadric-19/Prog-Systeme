import socket
import time
import os
import subprocess  # pour lancer cp sans fork

HOST = ''
PORT = 12345
SAVE_DIR = "/home/save"

os.makedirs(SAVE_DIR, exist_ok=True)

s = socket.socket()
s.bind((HOST, PORT))
s.listen(5)
print("Serveur pret...")

while True:
    client, addr = s.accept()
    chemin = client.recv(1024).decode()
    client.close()

    if not os.path.isfile(chemin):
        print("Fichier inexistant :", chemin)
        continue

    # extraire nom fichier
    nom = os.path.basename(chemin)

    # date
    t = time.localtime()
    date = f"{t.tm_year}_{t.tm_mon+1:02d}_{t.tm_mday:02d}"

    # nom final
    dest_path = os.path.join(SAVE_DIR, f"{addr[0]}_{date}_{nom}")

    # lancer commande cp subprocess
    try:
        subprocess.run(["/bin/cp", chemin, dest_path], check=True)
        print("Fichier copie :", dest_path)
    except subprocess.CalledProcessError:
        print("Erreur lors de la copie :", chemin)