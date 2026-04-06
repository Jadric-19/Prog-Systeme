import os
import sys
import signal

if len(sys.argv) != 2:
    print(f"Usage: {sys.argv[0]} <PID_affiche>")
    sys.exit(1)

pid_affiche = int(sys.argv[1])

# Saisie de l'entier
entier = int(input("Saisir un entier : "))

# Ecriture dans le fichier
try:
    with open("/tmp/entier.txt", "w") as f:
        f.write(f"{entier}\n")
except IOError as e:
    print("Erreur lors de l'écriture :", e)
    sys.exit(1)

# Envoi du signal au processus affiche
try:
    os.kill(pid_affiche, signal.SIGUSR1)
    print(f"Signal envoye au processus {pid_affiche}")
except OSError as e:
    print("Erreur lors de l'envoi du signal :", e)
    sys.exit(1)