/*Exercice 3.3 (∗) Ecrire un programme qui saisit un nom de fichier texte au clavier et ouvre ce
fichier dans l’éditeur emacs, dont le fichier exécutable se trouve à l’emplacement /usr/bin/emacs.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char nom_fichier[256];
    char commande[512];

    printf("Entrez le nom du fichier : ");
    fgets(nom_fichier, sizeof(nom_fichier), stdin);

    nom_fichier[strcspn(nom_fichier, "\n")] = '\0';

    strcpy(commande, "/usr/bin/emacs \"");
    strcat(commande, nom_fichier);
    strcat(commande, "\"");

    system(commande);

    return 0;
}