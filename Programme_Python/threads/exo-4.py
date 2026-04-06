import threading
import random
import time

class TypeTableau:
    def __init__(self, nb1, nb2):
        self.tab1 = [0] * nb1
        self.tab2 = [0] * nb2
        self.nb1 = nb1
        self.nb2 = nb2

def thread_initial(t: TypeTableau, stop_flag):
    random.seed(time.time())
    for i in range(t.nb1):
        if stop_flag[0]:
            return
        t.tab1[i] = random.randint(1, 100)
    for i, val in enumerate(t.tab1):
        print(f"Tab1[{i+1}] = {val}")

    print("\n")
    for i in range(t.nb2):
        if stop_flag[0]:
            return
        t.tab2[i] = random.randint(1, 100)
    for i, val in enumerate(t.tab2):
        print(f"Tab2[{i+1}] = {val}")

def thread_inclu(t: TypeTableau, resultat: list, stop_flag):
    tmp = 0
    for val1 in t.tab1:
        if stop_flag[0]:
            return
        if val1 in t.tab2:
            tmp += 1
    resultat[0] = tmp

def thread_exit(stop_flag):
    while not stop_flag[0]:
        c = input("\nPour quitter appuyer sur 'A' : ").strip().upper()
        if c == 'A':
            print("\n---------------- Annulation du programme --------------------\n")
            stop_flag[0] = True

def main():
    nb1 = 6
    nb2 = 11

    t = TypeTableau(nb1, nb2)
    stop_flag = [False]

    
    thread3 = threading.Thread(target=thread_exit, args=(stop_flag,))
    thread3.start()

   
    thread1 = threading.Thread(target=thread_initial, args=(t, stop_flag))
    thread1.start()
    thread1.join()

    if stop_flag[0]:
        return

    
    resultat = [0]
    thread2 = threading.Thread(target=thread_inclu, args=(t, resultat, stop_flag))
    thread2.start()
    thread2.join()

    if stop_flag[0]:
        return

    if resultat[0] == t.nb1:
        print("\n--------------- T1 est inclus dans T2 ----------------\n")
    else:
        print("\n--------------- T1 n'est pas inclus dans T2 ----------------\n")

if __name__ == "__main__":
    main()