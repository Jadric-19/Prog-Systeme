/*Ecrire un programme qui saisit les valeurs d’un tableau d’entier tab de n
éléments alloué dynamiquement. L’entier n sera saisi au clavier. Le programme affiche la valeur
d’un élément tab[i] où i est saisi au clavier. En cas d’erreur de segmentation le programme
fait resaisir la valeur de i avant de l’afficher.*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#define TRUE 1

sigjmp_buf env;

int i = 0  , erreur = 0 ;
void gestionnaire(int sig) 
{
    if(sig == SIGSEGV)
     {
        printf("Erreur : indice invalide ! Veuillez resaisir un indice correct.\n");
        erreur = 1 ;
        siglongjmp(env, 1) ;
     }
} 

int main() 
{
    int n;
    int *tab;

    struct sigaction action ;

    action.sa_handler = gestionnaire; 
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0 ;

    if (sigaction(SIGSEGV, &action, NULL) != 0)
    {
        fprintf(stderr, "Erreur sigaction\n");
        exit(1);
    }

    printf("Saisir le nombre d'elements du tableau: ");
    scanf("%d", &n);

    tab = malloc(sizeof(int) * n);
    if (!tab) 
    {
        perror("Erreur allocation");
        return 1;
    }

    for ( i = 0 ; i < n; i++) 
    {
        printf("tab[%d] = ", i);
        scanf("%d", &tab[i]);
    }

    i = 0 ;

    while (TRUE) 
    {
        if (sigsetjmp(env , 1) == 0 || erreur ) 
        {
            if(erreur)
               erreur = 0 ;
          
            printf("Saisir l'indice de l'element a afficher: ");
            scanf("%d", &i);   
             
        }
        printf("tab[%d] = %d\n", i , tab[i]);
        break; 
    }

    free(tab);
    return 0;
}