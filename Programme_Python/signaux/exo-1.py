import os
import signal
import time
import sys
from threading import Event

# Evnement pour gerer la mise en pause du fils
pause_event = Event()
pause_event.set()  

def gestionnaire(signum, frame):
    if signum == signal.SIGUSR1:
        print("\n---------- REDÉMARRAGE DU FILS ---------")
        pause_event.set()  # Debloque le fils
    elif signum == signal.SIGUSR2:
        print("\n---------- FILS ENDORMI ------------")
        pause_event.clear()  # Met le fils en pause

def fils():
    # Installer les handlers pour SIGUSR1 et SIGUSR2
    signal.signal(signal.SIGUSR1, gestionnaire)
    signal.signal(signal.SIGUSR2, gestionnaire)

    compteur = 0
    while True:
        pause_event.wait() 
        print(f"\n---- {compteur} ----")
        compteur += 1
        time.sleep(2)

def main():
    pid = os.fork()
    
    if pid == 0:
        # Processus fils
        fils()
    else:
        # Processus pere
        while True:
            try:
                rep = input("\n==> (s) pour endormir le fils, (r) pour le redemarrer, (q) pour le tuer : ").strip()
                if rep == 's':
                    os.kill(pid, signal.SIGUSR2)
                elif rep == 'r':
                    os.kill(pid, signal.SIGUSR1)
                elif rep == 'q':
                    os.kill(pid, signal.SIGKILL)
                    print("Fils tue. Fin du programme.")
                    break
                else:
                    print("\n--- SIGNAL NON REPERTORIE ----")
            except KeyboardInterrupt:
                os.kill(pid, signal.SIGKILL)
                print("\nProgramme interrompu. Fils tué.")
                break

if __name__ == "__main__":
    main()