/*
  Écrire un programme qui saisit au clavier un tableau d’entiers et sauve-
 garde ce tableau au format binaire dans un fichier ayant permission en écriture pour le groupe
 du fichier et en lecture seule pour les autres utilisateurs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h> 
#include <unistd.h>


// Fonction saisit un tableau et le sauvegarde en binaire avec les permissions

void ecriture_binaire(const char *fichier, int n) 
{
     int *tab = malloc(n * sizeof(int));

     if (tab == NULL) 
     {
        perror("Erreur d'allocation memoire");
        return;
     }

     printf("Entrez %d entiers :\n", n);
     for (int i = 0; i < n; i++) 
     {
         printf("==> ") ;
         if (scanf("%d", &tab[i]) != 1) 
         {
             printf("Entree invalide.\n");
             free(tab);
             return;
         }
     }

     int fd = open(fichier, O_WRONLY | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR | S_IWGRP | S_IROTH);
     if (fd == -1) 
     {
        perror("Erreur ouverture fichier");
        free(tab);
        return;
     }

     
     ssize_t bytes = write(fd , tab , sizeof(int) * n ) ;
     if(bytes != (ssize_t) (sizeof(int) * n) )
     {
        perror("Erreur ecriture fichier");
        close(fd);
        free(tab);
        return;
     }

     close(fd);
     free(tab);


     printf("Tableau sauvegarde dans '%s' avec les permissions correctes.\n", fichier);

}

int main() 
{
     int n = 0 ;
     char nom_fichier[] = "tableau.bin" ;

     printf("Entrez le nombre d'entiers du tableau : ");
     if (scanf("%d", &n) != 1 || n <= 0) 
     {
         printf("Nombre invalide.\n");
         return 1;
     }

  
     ecriture_binaire(nom_fichier, n);

     return 0;
}