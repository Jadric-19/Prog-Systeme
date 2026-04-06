import os
import struct

def ecriture_binaire(fichier, n):
    tab = []

    # Saisie des elements
    print(f"Entrez {n} entiers :")
    for i in range(n):
        while True:
            try:
                val = int(input(f"==> "))
                tab.append(val)
                break
            except ValueError:
                print("Entrée invalide. Veuillez entrer un entier.")

    # ouverture du fichier en mode binaire
    try:
        with open(fichier, "wb") as f:
            # On écrit les entiers en binaire
            for val in tab:
                # 'i' = int (4 octets), format standard C
                f.write(struct.pack('i', val))
    except OSError as e:
        print(f"Erreur ouverture ou écriture fichier : {e}")
        return

    # Définition des permissions : écriture pour le groupe, lecture pour les autres
    # 0o620 = rw--w---- (groupe write, autres read) ; adapté de l'exemple C
    # Si tu veux exactement comme C : rw------- (owner) | rw- (group) | r-- (others) => 0o764
    try:
        os.chmod(fichier, 0o624)  # rw- r-- -w-
    except OSError as e:
        print(f"Erreur chmod fichier : {e}")
        return

    print(f"Tableau sauvegardé dans '{fichier}' avec les permissions correctes.")


if __name__ == "__main__":
    try:
        n = int(input("Entrez le nombre d'entiers du tableau : "))
        if n <= 0:
            print("Nombre invalide.")
        else:
            ecriture_binaire("tableau.bin", n)
    except ValueError:
        print("Entrée invalide.")