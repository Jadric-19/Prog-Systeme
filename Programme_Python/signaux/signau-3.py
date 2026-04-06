import os
import signal
import time
import sys

N = 5
pids = []

def gestionnaire_fils(signum, frame):
    if signum == signal.SIGUSR1:
        print(f"Fils {os.getpid()}: je suis réveillé !")
    elif signum == signal.SIGUSR2:
        print(f"Fils {os.getpid()}: je m'endors...")
        signal.pause() 
    elif signum == signal.SIGTERM:
        print(f"Fils {os.getpid()}: je suis tué !")
        sys.exit(0)

def gestionnaire_pere(signum, frame):
    if signum == signal.SIGTERM:
        print(f"Père {os.getpid()}: je suis tué !")
        sys.exit(0)

def creer_fils():
    global pids
    for i in range(N):
        pid = os.fork()
        if pid < 0:
            print("Erreur fork")
            sys.exit(1)
        elif pid == 0:
            # Fils
            signal.signal(signal.SIGUSR1, gestionnaire_fils)
            signal.signal(signal.SIGUSR2, gestionnaire_fils)
            signal.signal(signal.SIGTERM, gestionnaire_fils)

            j = 0
            while True:
                print(f"Fils {os.getpid()}: boucle {j}")
                j += 1
                time.sleep(2)
            sys.exit(0)
        else:
            # Pere stocke le PID
            pids.append(pid)

def menu():
    print("\n -------------MENU :-------------")
    print("1 - Endormir un fils")
    print("2 - Réveiller un fils")
    print("3 - Terminer un fils")
    print("4 - Terminer le père")
    choix = int(input("==> Votre choix: "))
    return choix

def traiter_choix(choix):
    if 1 <= choix <= 3:
        fils_num = int(input(f"Numéro du fils (1-{N}): "))
        if fils_num < 1 or fils_num > N:
            print("Fils invalide !")
            return
        pid_fils = pids[fils_num - 1]

    if choix == 1:
        os.kill(pid_fils, signal.SIGUSR2)
    elif choix == 2:
        os.kill(pid_fils, signal.SIGUSR1)
    elif choix == 3:
        os.kill(pid_fils, signal.SIGTERM)
    elif choix == 4:
        os.kill(os.getpid(), signal.SIGTERM)
    else:
        print("Choix invalide !")

def main():
    # Gestionnaire pour tuer le pere
    signal.signal(signal.SIGTERM, gestionnaire_pere)

    # Creation des fils
    creer_fils()

    # Boucle menu
    while True:
        choix = menu()
        traiter_choix(choix)

if __name__ == "__main__":
    main()