/*Dans un programme prévu pour utiliser des threads, créer un compteur
global pour compter le nombre d’itérations, et une variable globale réelle u. Dans le main, on
initialisera u à la valeur 1
Le programme crée deux threads T1 et T2. Dans chaque thread Ti, on incrémente le comp-
teur du nombre d’itération, et on applique une affectation :
u = f_i(u);
pour une fonction f_i qui dépend du thread.

f _1(x) = (x − 1)2 et f _2(x) = (x − 2)2

De plus, le thread affiche la valeur de u et attend un temps aléatoire (entre 1 et 5 secondes)
entre deux itérations.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

pthread_mutex_t my_mutex = PTHREAD_MUTEX_INITIALIZER ;
double compt = 0 , u = 0 , max = 10 ;

void *thread_t1(void *arg)
{
     int i = 0 , temps = 0 ;

     while(compt < max)
      { 
          temps = rand() % 5 + 1 ;
          pthread_mutex_lock(&my_mutex) ; 
          u = ( 1.0 / 4) * pow((u - 1) , 2) ;
          compt++ ;
          printf("\n----- U = %f ------\n" , u) ;
          pthread_mutex_unlock(&my_mutex) ;
          sleep(temps) ;
      }
     pthread_exit(NULL) ;
}


void *thread_t2(void *arg)
{
     int i = 0 , temps = 0 ;

     while(compt < max)
      { 
          temps = rand() % 5 + 1 ;
          pthread_mutex_lock(&my_mutex) ; 
          u = ( 1.0 / 6) * pow((u - 2),2) ;
          compt++ ;
          printf("\n----- U = %f ------\n",u) ;
          pthread_mutex_unlock(&my_mutex) ;
          sleep(temps) ;
      }
     pthread_exit(NULL) ;
}


int main()
{
     pthread_t T1 , T2 ;
     int ret = 0 ;
     
     srand(time(NULL)) ;
     u = 1 ;

     ret = pthread_create(&T1 , NULL , thread_t1 , NULL) ;
     if(ret != 0 )
      {
          printf("\n ERREUR : THREAD T1 \n") ;
          exit(0) ;
      }
     ret = 0 ;
     ret = pthread_create(&T2 , NULL , thread_t2 , NULL) ;

     if(ret != 0 )
      {
          printf("\n ERREUR : THREAD T2 \n") ;
          exit(0) ;
      }
     
     pthread_join(T1 , NULL) ;
     pthread_join(T2 , NULL) ;

     
     return 0 ;

}