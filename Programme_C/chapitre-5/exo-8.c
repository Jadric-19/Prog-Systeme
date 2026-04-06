/*(Problème du rendez-vous)
a) Les sémaphores permettent de réaliser simplement des rendez-vous Deux threads T1 et T2
itèrent un traitement 10 fois. On souhaite qu’à chaque itération le thread T1 attende à la fin de
son traitement qui dure 2 secondes le thread T2 réalisant un traitement d’une durée aléatoire
entre 4 et 9 secondes. Écrire le programme principal qui crée les deux threads, ainsi que les
fonctions de threads en organisant le rendez-vous avec des sémaphores*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define N 10

sem_t sem ;

void *thread_T1(void *arg)
{
    for(int i = 0; i < N; i++)
    {
        printf("T1 : debut iteration %d\n", i);

        sleep(2);  

        printf("T1 : attend T2\n");
        sem_wait(&sem);  

        printf("T1 : reprend iteration %d\n", i);
    }

    pthread_exit(NULL);
}


void *thread_T2(void *arg)
{
    for(int i = 0; i < N; i++)
    {
        printf("T2 : debut iteration %d\n", i);

        int t = rand() % 6 + 4 ; 
        sleep(t);

        printf("T2 : fin iteration %d (temps=%d)\n", i, t);

        sem_post(&sem) ; 
    }

    pthread_exit(NULL);
}



int main(int argc , char *argv[])
{
    pthread_t th1, th2;

    srand(time(NULL));

    sem_init(&sem, 0 , 0);

    pthread_create(&th1, NULL, thread_T1, NULL);
    pthread_create(&th2, NULL, thread_T2, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    sem_destroy(&sem);

    return 0;
}