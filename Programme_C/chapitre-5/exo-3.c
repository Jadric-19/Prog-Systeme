/*Créer une structure TypeTableau qui contient :
• Un tableau d’entiers ;
• Le nombre d’éléments du tableau ;
• Un entier x.
Écrire un programme qui crée un thread qui initialise un TypeTableau avec des valeurs
aléatoires entre 0 et 99. Le nombre d’éléments du tableau est passé en paramètre. Dans le
même temps, le thread principal lit un entiers x au clavier. Lorsque le tableau est fini de
générer, le programme crée un thread qui renvoie 1 si l’élément x est dans le tableau, et 0
sinon.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#define TAILLE 100

typedef struct
{
    int *tab ;
    int nb ;
    int x ;
}TypeTableau ;


void* thread_initial(void *arg)
{
   
   TypeTableau *t1 = (TypeTableau*)arg ;
   int i = 0 , j = 0 ;

   t1->tab = malloc(sizeof(int) * TAILLE) ;
   srand(time(NULL)) ;
   

   for(i = 0 ; i < TAILLE ; i++)
    {
        
        j = rand() % 100 + 1 ;
        t1->tab[i] = j ;
    }

   for(i = 0 ; i  < TAILLE ; i++)
    {
        printf("\n Tab[%d] = %d \n" , i+1 , t1->tab[i]) ;
    }
   
  
    pthread_exit(NULL) ;
}


void *thread_recheche(void *arg)
{
    TypeTableau *t1 = (TypeTableau*)arg ;
    int *j = malloc(sizeof(int)) ;
    int i = 0  ;

    for(i = 0 ; i < TAILLE ; i++)
    {
        if(t1->tab[i] == t1->x)
         {
            *j = 1 ;
            break ;
         }
    }
    
    pthread_exit(j) ;
}


int main() 
{
    pthread_t thread1 , thread2 ;
    TypeTableau t1 ;

    int i = 0 , ret = 0 , x = 0 ;
    int *tmp = NULL ;

    ret = pthread_create(&thread1 , NULL , thread_initial , &t1) ;

    if(ret != 0)
     {
        perror("THREAD-1 : ERREUR ") ;
        exit(0) ;
     }

    pthread_join(thread1 , NULL) ;

    ret = 0 ;
    printf("\n Entreer x : ") ;
    scanf("%d" , &t1.x) ;

    ret = pthread_create(&thread2 , NULL , thread_recheche , &t1) ;

    if(ret != 0)
     {
        perror("THREAD-2 : ERREUR ") ;
        exit(0) ;
     }
    
    pthread_join(thread2 , (void**)&tmp) ;
    
    int test = *(int*)tmp ;

    if(test == 1)
     {
        printf("\nValeur trouver \n") ;
     }
    else
     {
        printf("\n Valeur non trouver\n");
     }
    
    
  
    free(tmp) ;
    
    return 0 ;
    
}