import threading

TAILLE = 10

def fonction_thread(tab):
    for i in range(TAILLE):
        print(f"Tab[{i}] = {tab[i]}")

def main():
    tableau = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]

    # Creation du thread
    thread = threading.Thread(target=fonction_thread, args=(tableau,))
    thread.start()

    # Attente de la fin du thread
    thread.join()

if __name__ == "__main__":
    main()