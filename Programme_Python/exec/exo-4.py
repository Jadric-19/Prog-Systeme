import os

print("Programme de copie du repertoire courant.")
print("Entrez 'quit' pour quitter.")

while True:
    rep = input("Entrez un nom de repertoire de destination : ").strip()

    if rep.lower() == "quit":
        print("Fin du programme.")
        break

    commande = f'cp -r . "{rep}"'
    
    # Executer la commande
    ret = os.system(commande)
    
    if ret != 0:
        print("Erreur lors de l'execution de la commande")
    else:
        print(f"Copie terminee dans {rep}")