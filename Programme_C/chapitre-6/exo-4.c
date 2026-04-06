/*
Écrire une programme qui charge en mémoire un tableau d’entiers tel que généré au a). Le
fichier d’entiers ne contient pas le nombre d’éléments. Le programme doit fonctionner pour un
nombre quelconque de données entières dans le fichier.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int *lecture_binaire(const char *fichier, int *taille) 
{
    int fd = open(fichier, O_RDONLY) ;
    
    if (fd == -1) 
    {
        perror("Erreur ouverture fichier") ;
        return NULL;
    }

    int capacite = 10 ;          
    int *tab = malloc(capacite * sizeof(int)) ;

    if (!tab) 
    {
        perror("Erreur allocation memoire") ;
        close(fd) ;
        return NULL ;
    }

    int n = 0 ;  
    int buffer ;
    ssize_t bytes ;

    while ((bytes = read(fd, &buffer, sizeof(int))) == sizeof(int)) 
    {
        if (n >= capacite) 
        {
            capacite *= 2 ; 

            int *tmp = realloc(tab, capacite * sizeof(int)) ;
            if (!tmp) 
            {
                perror("Erreur realloc") ;
                free(tab) ;
                close(fd) ;
                return NULL ;
            }

            tab = tmp ;
        }

        tab[n++] = buffer ;
    }

    if (bytes == -1) 
    {
        perror("Erreur lecture fichier");
        free(tab);
        close(fd);
        return NULL;
    }

    close(fd);
    *taille = n ; 
    return tab;
}

int main() 
{
     char nom_fichier[] = "tableau.bin" ;
     int taille ;
     int *tab = lecture_binaire(nom_fichier, &taille) ;

     if (!tab) 
     {
        perror("ERREUR DE RECUPERATION") ;
        return 1 ;
     }
 
     int i = 0 ;
     
     printf("Tableau charge (%d elements) :\n", taille) ;
     for (i = 0 ; i < taille ; i++) 
     {
        printf("%d ", tab[i]) ;
     }

     printf("\n") ;

     free(tab) ;
     return 0;
}