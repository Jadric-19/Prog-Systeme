/*Exercice 3.2 (∗) Ecrire un programme qui prend en argument un chemin vers un répertoire
R, et copie le répertoire courant dans ce répertoire R. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAILLE 256

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage : %s <repertoire_destination>\n", argv[0]);
        return 1;
    }

    char commande[TAILLE] = "cp -r . ";

    strcat(commande, argv[1]); 

    system(commande);

    printf("Copie terminee !\n");

    return 0;
}