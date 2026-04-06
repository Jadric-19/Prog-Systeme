import threading
import random

TAILLE = 100

def fonction_thread(result):
    tab = []
    for i in range(TAILLE):
        val = random.randint(0, 99)
        tab.append(val)
    result['tab'] = tab

def main():
    result = {}
    thread = threading.Thread(target=fonction_thread, args=(result,))
    thread.start()
    thread.join()

    tab = result.get('tab', [])
    for i in range(len(tab)):
        print(f"Tab[{i}] = {tab[i]}")

if __name__ == "__main__":
    main()