import os

for i in range(5):
    try:
        pid = os.fork()
    except OSError as e:
        print("Erreur fork :", e)
        exit(1)

    if pid == 0:
        print(f"Je suis le Fils {i+1} , PID={os.getpid()}, PID du père={os.getppid()}")
        break  

print(f"Processus PID={os.getpid()} termine sa boucle.")