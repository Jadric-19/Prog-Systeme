/*Écrire un programme qui crée un thread qui alloue un tableau d’entiers,
initialise les éléments par des entiers aléatoires entre 0 et 99, et retourne le tableau d’entiers.*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#define TAILLE 100

void* fonction_thread(void *arg)
{
   int *tab = (int*)arg ;
   int j = 0 ;

   tab = malloc(sizeof(int) * TAILLE) ;
   srand(time(NULL)) ;
   

   for(int i = 0 ; i < TAILLE ; i++)
    {
        
        j = rand() % 100 + 1 ;
        tab[i] = j ;
    }

   /*for(int i = 0 ; i  < TAILLE ; i++)
    {
        printf("\n Tab[%d] = %d \n" , i+1 , tab[i]) ;
    }*/
   
    pthread_exit(tab) ;
}

int main() 
{
    pthread_t thread ;

    int i = 0 , ret = 0 ;

    int *pt = NULL ;

    ret = pthread_create(&thread , NULL , fonction_thread , pt) ;
    if(ret != 0)
     {
        perror("THREAD : ERREUR \n") ;
        exit(0) ;
     }
    
   
    pthread_join( thread , (void**)&pt ) ;
  
    free(pt) ;
    
    return 0 ;
    
}