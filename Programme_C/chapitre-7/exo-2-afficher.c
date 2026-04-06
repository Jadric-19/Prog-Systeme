/*Ecrire un programme saisit.c qui saisit un int au clavier, et l’enregistre
dans un fichier /tmp/entier.txt. Écrire un programme affiche.c qui attend (avec sleep) un
signal utilisateur du programme saisit.c. Lorsque l’entier a été saisi, le programme affiche.c
affiche la valeur de l’entier.*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int signal_recu = 0;

void gestionnaire(int sig) 
{
    signal_recu = 1;  
}

int main() 
{
   
    struct sigaction sa;
    sa.sa_handler = gestionnaire;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGUSR1, &sa, NULL) == -1) 
     {
        perror("sigaction");
        return 1;
     }

    printf("PID du processus affiche : %d\n", getpid());
    printf("En attente du signal...\n");


    while (!signal_recu) 
     {
        sleep(1);
     }

   
    FILE *fichier = fopen("/tmp/entier.txt", "r");

    if (!fichier) 
     {
        perror("fopen() : ");
        return 1;
     }

    int entier = 0 ;
    if (fscanf(fichier, "%d", &entier) != 1) 
     {
        printf("\n-----Erreur lecture entier----\n");
        fclose(fichier);
        return 1;
     }

    fclose(fichier);

    printf("Entier reçu : %d\n", entier);
    return 0;
}