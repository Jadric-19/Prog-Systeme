import struct
import os

def lecture_binaire(fichier):
    tab = []

    if not os.path.isfile(fichier):
        print(f"Erreur : le fichier '{fichier}' n'existe pas.")
        return None

    try:
        with open(fichier, "rb") as f:
            while True:
                bytes_read = f.read(4)  # taille d'un int (4 octets)
                if not bytes_read:
                    break
                if len(bytes_read) != 4:
                    print("Erreur : taille du bloc lue incorrecte")
                    return None
                # 'i' = int 4 octets, format standard C
                val = struct.unpack('i', bytes_read)[0]
                tab.append(val)
    except OSError as e:
        print(f"Erreur lecture fichier : {e}")
        return None

    return tab


if __name__ == "__main__":
    nom_fichier = "tableau.bin"
    tab = lecture_binaire(nom_fichier)

    if tab is None:
        print("ERREUR DE RECUPERATION")
    else:
        print(f"Tableau chargé ({len(tab)} éléments) :")
        print(" ".join(str(x) for x in tab))