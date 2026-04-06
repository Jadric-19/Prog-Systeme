/*Exercice 3.5 (∗∗) : Ecrire un programme qui saisit des nom de fichiers texte au clavier et
ouvre tous ces fichiers dans l’éditeur emacs. Le programme doit se poursuivre jusqu’à ce que
l’utilisateur demande de quitter.*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1

int main()
{
    char fichier[256];
    char commande[512];
    int ret = 0 ;

    printf("Programme pour ouvrir des fichiers dans Emacs.\n");
    printf("Entrez 'quit' pour quitter.\n");

    while (TRUE)
    {
        printf("Entrez le nom d'un fichier texte : ");
        if (!fgets(fichier, sizeof(fichier), stdin)) 
        {
            break; 
        }


        fichier[strcspn(fichier, "\n")] = '\0';

       
        if (strcmp(fichier, "quit") == 0) 
        {
            printf("Fin du programme.\n");
            break;
        }

        strcpy(commande, "/usr/bin/emacs \"");
        strcat(commande, fichier);
        strcat(commande, "\"");

        ret = system(commande);

        if (ret == -1) 
        {
            perror("Erreur lors de l'execution de system");
        } 
        else 
        {
            printf("Fichier %s ouvert dans Emacs.\n", fichier);
        }
    }

    return 0;
}