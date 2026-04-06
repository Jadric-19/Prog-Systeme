import os
import sys

fichier = "test.txt"

r, w = os.pipe()

pid = os.fork()

if pid == 0:  # fils
    os.close(r)
    mot = input("Entrez un mot : ")  # faire input avant redirection
    os.dup2(w, 1)  # rediriger stdout pour envoyer mot au parent
    print(mot, flush=True)
    os.close(w)
    os._exit(0)

else:  
    os.close(w) 
    mot = os.read(r, 1024).decode().strip()  
    os.close(r)

    with open(fichier, 'r') as f:
        texte = f.read().split()
 
    res = 1 if mot in texte else 0
    if res :
        print("Mot trouve !")
    else :
        print("Mot inconnu ! ")

    os.waitpid(pid, 0)