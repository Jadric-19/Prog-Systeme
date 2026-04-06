import os

print("Programme pour ouvrir des fichiers dans Emacs.")
print("Entrez 'quit' pour quitter.")

while True:
    fichier = input("Entrez le nom d'un fichier texte : ").strip()

    if fichier.lower() == "quit":
        print("Fin du programme.")
        break

    # Construire la commande 
    commande = f'/usr/bin/emacs "{fichier}"'
    
    # Executer la commande
    ret = os.system(commande)

    if ret != 0:
        print("Erreur lors de l'execution de la commande")
    else:
        print(f"Fichier {fichier} ouvert dans Emacs.")