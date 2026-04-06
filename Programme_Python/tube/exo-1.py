import os

fichier = "test.txt"  # fichier texte à lire


r, w = os.pipe()

pid = os.fork()

if pid == 0:  # processus fils
    os.close(r)  
    mot = input("Entrez un mot : ")
    os.write(w, mot.encode())  
    os.close(w)
    os._exit(0)  

else: 
    os.close(w) 
    mot = os.read(r, 1024).decode()  # lire le mot du fils
    os.close(r)

    with open(fichier, 'r') as f:
        texte = f.read().split()  # liste des mots

    res = 1 if mot in texte else 0
    if res :
         print("Mot trouve !")
    else :
         print("Mot inconnu !")

    os.waitpid(pid, 0)  # attendre la fin du fils