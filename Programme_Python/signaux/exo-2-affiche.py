import signal
import time
import os

signal_recu = False

def gestionnaire(sig, frame):
    global signal_recu
    signal_recu = True

# Installer le gestionnaire pour SIGUSR1
signal.signal(signal.SIGUSR1, gestionnaire)

print(f"PID du processus affiche : {os.getpid()}")
print("En attente du signal...")

# Boucle d'attente
while not signal_recu:
    time.sleep(1)

# Lecture du fichier apres reception du signal
try:
    with open("/tmp/entier.txt", "r") as f:
        entier = int(f.readline())
except IOError:
    print("Erreur lors de la lecture du fichier")
    exit(1)
except ValueError:
    print("Erreur : contenu du fichier non valide")
    exit(1)

print(f"Entier recu : {entier}")