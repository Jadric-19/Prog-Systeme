/*Exercice 4.1 (exob asepipe) Écrire un programme qui crée deux processus. Le processus père
ouvre un fichier texte en lecture. On suppose que le fichier est composé de mots formés de
caractères alphabétiques séparés par des espaces. Le processus fils saisit un mot au clavier. Le
processus père recherche le mot dans le fichier, et transmet au fils la valeur 1 si le mot est dans
le fichier, et 0 sinon. Le fils affiche le résultat.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define TAILLE 100

int main() 
{
    int pipe1[2]; // fils - pere
    int pipe2[2]; // pere -  fils

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) 
    {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) 
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0) 
    { 
        close(pipe1[0]); 
        close(pipe2[1]); 

        char mot[TAILLE];
        printf("Entrez un mot : ");
        fflush(stdout);
        scanf("%s", mot);

       
        write(pipe1[1], mot, strlen(mot)+1);
        close(pipe1[1]); 

        
        int res;
        read(pipe2[0], &res, sizeof(int));
        close(pipe2[0]);

        if (res)
        {
            printf("Mot trouvé dans le fichier.\n");
        }
        else
        {
            printf("Mot non trouvé.\n");
        }

        exit(0);
    } 
    else 
    {
        close(pipe1[1]); 
        close(pipe2[0]);

        char mot_fils[TAILLE];
        read(pipe1[0], mot_fils, TAILLE);
        close(pipe1[0]);

        FILE *f = fopen("fichier.txt", "r");
        if (!f) 
        {
            perror("fichier");
            exit(1);
        }

        char mot[TAILLE];
        int trouve = 0;
        while (fscanf(f, "%s", mot) == 1) 
        {
            if (strcmp(mot, mot_fils) == 0) 
            {
                trouve = 1;
                break;
            }
        }
        fclose(f);

        
        write(pipe2[1], &trouve, sizeof(int));
        close(pipe2[1]);

        wait(NULL);
    }

    return 0;
}