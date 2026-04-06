import os
import sys

# Taille seuil : 1 Mo
TAILLE = 1048576

def traitement(rep):
    if not os.path.isdir(rep):
        print(f"\nERREUR : {rep} n'est pas un répertoire valide")
        return

    print(f"\nLes fichiers supérieurs à 1 Mo dans {rep} sont :\n")

    try:
        for nom in os.listdir(rep):
            if nom in ('.', '..'):
                continue

            path = os.path.join(rep, nom)

            try:
                stats = os.stat(path)
            except OSError as e:
                print(f"Erreur accès fichier {path} : {e}")
                continue

            if os.path.isfile(path) and stats.st_size > TAILLE:
                print(f"Fichier: {path} | Taille: {stats.st_size} octets | UID: {stats.st_uid}")

    except OSError as e:
        print(f"Erreur ouverture répertoire {rep} : {e}")


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("\nVeuillez entrer au moins un répertoire en argument : python fichier.py rep1 ...\n")
        sys.exit(0)

    for rep in sys.argv[1:]:
        traitement(rep)