import threading
import random
import time

# Struct tableau
class TypeTableau:
    def __init__(self, nb):
        self.tab = [0] * nb
        self.nb = nb
        self.x = None

# Thread inializer
def thread_initial(t1: TypeTableau):
    random.seed(time.time())
    for i in range(t1.nb):
        t1.tab[i] = random.randint(0, 99)
    for i, val in enumerate(t1.tab):
        print(f"Tab[{i+1}] = {val}")


def thread_recherche(t1: TypeTableau, resultat: list):
    for val in t1.tab:
        if val == t1.x:
            resultat[0] = 1
            return
    resultat[0] = 0

def main():
    TAILLE = 100
    t1 = TypeTableau(TAILLE)

  
    thread1 = threading.Thread(target=thread_initial, args=(t1,))
    thread1.start()
    thread1.join()  

    # Lecture de x
    t1.x = int(input("\nEntrez x : "))

    resultat = [0]


    thread2 = threading.Thread(target=thread_recherche, args=(t1, resultat))
    thread2.start()
    thread2.join()  


    if resultat[0] == 1:
        print("\nValeur trouve")
    else:
        print("\nValeur non trouve")

if __name__ == "__main__":
    main()