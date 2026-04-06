/*Écrire un programme qui crée un thread qui prend en paramètre un tableau
d’entiers et l’affiche dans la console.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#define TAILLE 10

void* fonction_thread(void *arg)
{
   int *tab = (int*)arg ;

   for(int i = 0 ; i  < TAILLE ; i++)
    {
        printf("\n Tab[%d] = %d \n" , i , tab[i]) ;
    }
   
    pthread_exit(NULL) ;
}

int main() 
{
    pthread_t thread ;

    int i = 0 , ret = 0 ;

    int tableau[TAILLE] = {1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , 10 } ;
    int *pt = malloc(sizeof(int) * 10) ;

    ret = pthread_create(&thread , NULL , fonction_thread ,tableau) ;
    if(ret != 0)
     {
        perror("THREAD : ERREUR \n") ;
        exit(0) ;
     }

    pthread_join( thread , NULL ) ;
    
    free(pt) ;

    return 0 ;
    
}