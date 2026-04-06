/*Ecrire un programme saisit.c qui saisit un int au clavier, et l’enregistre
dans un fichier /tmp/entier.txt. Écrire un programme affiche.c qui attend (avec sleep) un
signal utilisateur du programme saisit.c. Lorsque l’entier a été saisi, le programme affiche.c
affiche la valeur de l’entier.*/

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) 
     {
        fprintf(stderr, "Usage: %s <PID_affiche>\n", argv[0]);
        return 1;
     }

    pid_t pid_affiche = atoi(argv[1]);
    int entier = 0 ;

    printf("Saisir un entier : ");
    scanf("%d", &entier);

   
    FILE *fichier = fopen("/tmp/entier.txt", "w");

    if (!fichier) 
     {
        perror("fopen");
        return 1;
     }

    fprintf(fichier, "%d\n", entier);
    fclose(fichier);

    if (kill(pid_affiche, SIGUSR1) == -1) 
    {
        perror("kill() :");
        return 1;
    }

    printf("Signal envoye au processus %d\n", pid_affiche);
    return 0;
}