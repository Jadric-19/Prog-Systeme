/*Écrire un programme, avec un compteur global compt, et qui crée deux
threads :
• Le premier thread itère l’opération suivante : on incrémente le compteur et attend un
temps alléatoire entre 1 et 5 secondes.
• Le deuxième thread affiche la valeur du compteur toutes les deux secondes.
Les accès au compteur seront bien sûr protégés par un mutex. Les deux threads se terminent
lorsque le compteur atteint une valeur limite passée en argument (en ligne de commande) au
programme.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER ;
int compt = 0 ;


void *thread_compteur(void *arg)
{
    int cmp = *(int*)arg ;
    time_t temps = 0 ;

   

    while(compt < cmp)
     {
         temps = rand() % 5 + 1 ;
         pthread_mutex_lock(&my_mutex) ;
         compt++ ;
         pthread_mutex_unlock(&my_mutex) ;
         sleep(temps) ;
     }
    
    pthread_exit(NULL) ;
}

void *thread_display(void *arg)
{
    int cmp = *(int*)arg ;
    int temps = 0 ;
    
    while(compt < cmp)
     {
         temps = 2 ;
         pthread_mutex_lock(&my_mutex) ;
         printf("\n-----   %d  -----\n",compt) ;
         pthread_mutex_unlock(&my_mutex) ;
         sleep(temps) ; 
     }
    
    pthread_exit(NULL) ;
}

int main(int argc , char *argv[])
{

     if(argc < 2)
      {
          printf("\n-----------IL FAUT 2 ARGUMENT POUR QUE LE PROGRAMME PUISSE MARCHER---------------\n") ;
          exit(0) ;
     }
    
     pthread_t thread1 , thread2 ;
     int nb = atoi(argv[1]) ;
     int *nb1 = malloc(sizeof(int)) ;

      srand(time(NULL)) ;
     *nb1 = nb ;

     pthread_create(&thread1 , NULL , thread_compteur , nb1) ;
     pthread_create(&thread2 , NULL , thread_display , nb1) ;
     pthread_join(thread1 , NULL) ;
     pthread_join(thread2 , NULL) ;
   
     free(nb1) ;

     return 0 ;

}