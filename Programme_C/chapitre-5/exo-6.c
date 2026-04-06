/*Créer un programme qui a en variable globale un tableau de N double,
avec N=100.
Dans le main, le tableau sera initialisé avec des valeurs réelles aléatoires entre 0 et 100, sauf
les valeurs tableau[0] et tableau[99] qui vallent 0.
Le programme crée deux threads :
• Le premier thread remplace chaque valeur tableau[i], avec i = 1,2,. . .,98 par la moyenne
(tableau[i-1]+tableau[i]+tableau[i+1])/3
Il attend ensuite un temps alléatoire entre 1 et 3 secondes ;
• Le deuxième thread affiche le tableau toutes les 4 secondes*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

#define N 100 
#define COEF 3

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER ;
double tab[N] ;

void *thread_initial(void *arg)
{
     int i = 0 , a = 1 , b = 100 ;
     
    
     tab[0] = 0 ;
     tab[N-1] = 0 ;

     for(i = 1 ; i < N-1 ; i++ )
      {
         tab[i] = a + (b - a) * ((double) rand() / RAND_MAX) ;
      }

     pthread_exit(NULL) ;
}

void *thread_moyen(void *arg)
{
     int i = 0 , temps = 0 ;
    
     for(i = 1 ; i < N-1 ; i++)
     {
        temps = rand() % 3 + 1 ;
        pthread_mutex_lock(&my_mutex) ;
        tab[i] = (tab[i-1]+tab[i]+tab[i+1]) / COEF ;
        pthread_mutex_unlock(&my_mutex) ;
        sleep(temps) ;
     }

    pthread_exit(NULL) ;
}

void *thread_display(void *arg)
{
     int i = 0 , temps = 3 ;

     for(i = 0 ; i < N ; i++)
      {
          pthread_mutex_lock(&my_mutex) ;
          printf("\n------ %f ------\n" , tab[i]) ;
          pthread_mutex_unlock(&my_mutex) ;
          sleep(temps) ;
      }
      

     pthread_exit(NULL) ;
}

int main()
{ 
     pthread_t thread1 , thread2 , thread3 ;

     int ret = 0 ;

     srand(time(NULL)) ;

     ret = pthread_create(&thread1 , NULL , thread_initial , NULL) ;
     if(ret != 0)
      {
          printf("\n ERREUR : THREAD-1 \n") ;
          exit(0) ;
      }  
     pthread_join(thread1 , NULL) ;

     ret = 0 ;
     ret = pthread_create(&thread2 , NULL , thread_moyen , NULL) ;
     if( ret != 0)
      {
          printf("\n ERREUR : THREAD-2 \n") ;
          exit(0) ;
      }
     
     ret = 0 ;
     ret = pthread_create(&thread3 , NULL , thread_display , NULL) ;
     if( ret != 0)
      {
          printf("\n ERREUR : THREAD-3 \n") ;
          exit(0) ;
      }
      
     pthread_join(thread2 , NULL) ;
     pthread_join(thread3 , NULL);
  
     return 0 ;
}