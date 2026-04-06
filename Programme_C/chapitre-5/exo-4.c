/*) Reprendre la fonction de thread de génération d’un tableau aléatoire
du 1. Le thread principal crée en parallèle deux tableaux T1 et T2, avec le nombre d’éléments
de T1 plus petit que le nombre d’élemnts de T2.
b) Lorsque les tableaux sont finis de générer, lancer un thread qui détermine si le tableau T1
est inclus dans le tableau T2. Quelle est la complexité de l’algorithme ?
c) Modifier le programme précédent pour qu’un autre thread puisse terminer le programme si
l’utilsateur appuie sur la touche ’A’ (par exit(0)). Le programme doit afficher un message en
cas d’annulation, et doit afficher le résultat du calcul sinon.*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#define TAILLE 100

typedef struct
{
    int *tab1 ;
    int *tab2 ;
    int nb1 , nb2 ;
}TypeTableau ;


void* thread_initial(void *arg)
{
   
     TypeTableau *t1 = (TypeTableau*)arg ;
     int i = 0 , j = 0 ;
  
     t1->tab1 = malloc(sizeof(int) * t1->nb1) ;
     t1->tab2 = malloc(sizeof(int) * t1->nb2) ;
     srand(time(NULL)) ;
   

     for(i = 0 ; i < t1->nb1 ; i++)
     {
        
         j = rand() % 100 + 1 ;
         t1->tab1[i] = j ;
     }

     for(i = 0 ; i  < t1->nb1 ; i++)
     {
         printf("\n Tab1[%d] = %d \n" , i+1 , t1->tab1[i]) ;
     }

     printf("\n\n") ;
     
     for(i = 0 ; i < t1->nb2 ; i++)
     {
        
         j = rand() % 100 + 1 ;
         t1->tab2[i] = j ;
     }

     for(i = 0 ; i  <  t1->nb2; i++)
     {
         printf("\n Tab2[%d] = %d \n" , i+1 , t1->tab2[i]) ;
     }

   
  
     pthread_exit(NULL) ;

}


void *thread_exit(void *arg)
{
     char *A = (char*)arg ;
    
     while(*A != 'A')
      {
         printf("\nPour quite appuier sur 'A'\n") ;
         scanf(" %c" , A) ;
         
      }
     printf("\n----------------Anulation du programme--------------------\n") ;
     exit(0) ;    

}

void *thread_inclu(void *arg)
{ 
     TypeTableau *t1 = (TypeTableau*)arg ;
     int tab[t1->nb1]  ;
     memset(tab, 0, sizeof(tab));
     int i = 0 , j = 0 , tmp = 0 ;
     int *ret = malloc(sizeof(int)) ;


     for(i = 0 ; i < t1->nb1 ; i++)
      {
          for(j = 0 ; j < t1->nb2 ; j++)
           {
               if(t1->tab1[i] == t1->tab2[j])
                {
                    tmp++ ;
                   
                    break ;
                }
           }
      }
     
     *ret = tmp ;
     pthread_exit(ret) ;



}

int main() 
{
     pthread_t thread1 , thread2 , thread3;
     TypeTableau t1 ;

     int i = 0 , ret = 0 , x = 0 ;
     int *pt = NULL , *tmp = NULL ;
     char *A  = malloc(sizeof(char));

   
     t1.nb1 = 5 + 1 ;
     t1.nb2 = 10 + 1 ;

     ret = pthread_create(&thread1 , NULL , thread_initial , &t1) ;

     if(ret != 0)
     {
         perror("THREAD-1 : ERREUR ") ;
         exit(0) ;
     }

     pthread_join(thread1 , NULL) ;
     
     ret = 0 ;
     
     ret = pthread_create(&thread2 , NULL , thread_inclu , &t1) ;
     
     if(ret != 0)
     {
         perror("THREAD-1 : ERREUR ") ;
         exit(0) ;
     }

     pthread_join(thread2 , (void**)&tmp) ;

     int inclu = *(int*)tmp ;

     if(inclu == t1.nb1)
      {
          printf("\n---------------T1 est include dans T2----------\n") ;
      }
     else
      {
          printf("\n----------------T1 n'est pas includde dans T2-------------\n");
      }
    
 

     ret = 0 ;
     *A = 'B' ;
     
     ret = pthread_create(&thread3 , NULL , thread_exit, A) ;
     
     if(ret != 0)
     {
         perror("THREAD-1 : ERREUR ") ;
         exit(0) ;
     }

     pthread_join(thread3 , NULL) ;

     free(tmp) ;
     free(A) ;
     free(t1.tab1) ;
     free(t1.tab2) ;



     return 0 ;
}