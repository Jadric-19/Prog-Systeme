
/*Exercice 3.1 : Écrire un programme qui prend deux arguments en ligne de commande en
supposant qu ce sont des nombres entiers, et qui affiche l’addition de ces deux nombres.*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage : %s nombre1 nombre2\n", argv[0]);
        return 1;
    }

    int a = atoi(argv[1]);
    int b = atoi(argv[2]);

    int somme = a + b;

    printf("La somme de %d et %d est : %d\n", a, b, somme);

    return 0;
}