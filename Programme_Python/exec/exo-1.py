import sys

if len(sys.argv) != 3:
    print(f"Usage : {sys.argv[0]} nombre1 nombre2")
    sys.exit(1)

# Recuperation en int
try:
    a = int(sys.argv[1])
    b = int(sys.argv[2])
except ValueError:
    print("Les arguments doivent être des nombres entiers.")
    sys.exit(1)

# Calcul et afficher la somme
somme = a + b
print(f"La somme de {a} et {b} est : {somme}")