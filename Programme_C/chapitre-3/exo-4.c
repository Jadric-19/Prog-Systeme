/*Exercice 3.4 (∗∗) Ecrire un programme qui saisit des noms de répertoires au clavier et copie
le répertoire courant dans tous ces répertoires. Le programme doit se poursuivre jusqu’à ce que
l’utilisateur demande de quitter le programme.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1

int main()
{
    char rep[256];
    char commande[512];
    int ret = 0 ;

    printf("Programme de copie du repertoire courant.\n");
    printf("Entrez 'quit' pour quitter.\n");

    while (TRUE)
    {
        printf("Entrez un nom de repertoire de destination : ");
        if (!fgets(rep, sizeof(rep), stdin)) 
        {
            break;
        }

        rep[strcspn(rep, "\n")] = '\0';

        if (strcmp(rep, "quit") == 0) 
        {
            printf("Fin du programme.\n");
            break;
        }

        strcpy(commande, "cp -r . \"");
        strcat(commande, rep);
        strcat(commande, "\"");

        ret = system(commande);

        if (ret == -1) 
        {
            perror("Erreur lors de l'execution de system");
        } 
        else 
        {
            printf("Copie terminee dans %s\n", rep);
        }
    }

    return 0;
}