import threading
import random
import time
import sys

# Compteur global
compt = 0
lock = threading.Lock()


def thread_compteur(limite):
    global compt
    while True:
        with lock:
            if compt >= limite:
                break
            compt += 1
            print(f"Compteur incremente: {compt}")
        temps = random.randint(1, 5)
        time.sleep(temps)


def thread_display(limite):
    global compt
    while True:
        with lock:
            if compt >= limite:
                break
            print(f"\n-----   {compt}  -----\n")
        time.sleep(2)

def main():
    if len(sys.argv) < 2:
        print("\n-----------IL FAUT 1 ARGUMENT POUR QUE LE PROGRAMME PUISSE MARCHER---------------\n")
        sys.exit(0)

    limite = int(sys.argv[1])

    t1 = threading.Thread(target=thread_compteur, args=(limite,))
    t2 = threading.Thread(target=thread_display, args=(limite,))

    t1.start()
    t2.start()

    t1.join()
    t2.join()

    print("\nProgramme terminé.")

if __name__ == "__main__":
    main()