/*Dans cette version N threads doivent se donner rendez-vous, N étant passé en argument au
programme. Les threads ont tous une durée aléatoire entre 1 et 5 secondes.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

int N;
int count = 0;

pthread_mutex_t mutex;
sem_t barriere;

void *thread_func(void *arg)
{
     int id = *(int*)arg;

    
     int t = 1 + rand() % 5;
     printf("Thread %d : travail pendant %d sec\n", id, t);
     sleep(t);

     printf("Thread %d : arrive au rendez-vous\n", id);

  
     pthread_mutex_lock(&mutex) ;
     count++ ;


     if(count == N)
     {
         printf("Thread %d : dernier arrivé, libère tout le monde\n", id);
         for(int i = 0; i < N; i++)
             sem_post(&barriere);
     }

     pthread_mutex_unlock(&mutex);

     sem_wait(&barriere);

     printf("Thread %d : passe la barrière\n", id);

     pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
     if(argc != 2)
     {
         printf("ERREUR MANQUE ARGUMENT : %s N\n", argv[0]);
         return 1;
     }

     N = atoi(argv[1]);

     pthread_t threads[N];
     int ids[N];
     int i = 0 ;

     srand(time(NULL));

     pthread_mutex_init(&mutex, NULL);
     sem_init(&barriere, 0, 0);

     for(i = 0; i < N; i++)
     {
         ids[i] = i;
         pthread_create(&threads[i], NULL, thread_func, &ids[i]);
     }

     for(i = 0; i < N; i++)
         pthread_join(threads[i], NULL);

     pthread_mutex_destroy(&mutex);
     sem_destroy(&barriere);

     return 0;
}