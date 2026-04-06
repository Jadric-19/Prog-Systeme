def main():
    
    n = int(input("Saisir le nombre d'elements du tableau: "))

   
    tab = []
    for i in range(n):
        val = int(input(f"tab[{i}] = "))
        tab.append(val)

    # Boucle pour saisir l'indice a afficher
    while True:
        try:
            i = int(input("Saisir l'indice de l'element a afficher: "))
            print(f"tab[{i}] = {tab[i]}")
            break  # Sort de la boucle si tout est correct
        except IndexError:
            print("Erreur : indice invalide ! Veuillez resaisir un indice correct.")
        except ValueError:
            print("Erreur : saisie non valide. Veuillez entrer un entier.")

if __name__ == "__main__":
    main()