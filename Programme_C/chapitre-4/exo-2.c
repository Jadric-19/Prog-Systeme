/*(R) eprendre les programmes de l’exercice ??. Nous allons faire un programme
qui fait la même chose, mais transmet les données différement. Dans le programme père, on
liera les flots stdout et stdin à un tube*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 256

int main()
{
    int pipefd[2];
    pid_t pid;

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork() ;

    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {

        close(pipefd[1]); 

        
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);

        char mot[MAX];
        
        scanf("%s", mot);  

        if (strcmp(mot, "1") == 0)
        {
            printf("Le mot est présent dans le fichier.\n");
        }
        else
        {
            printf("Le mot n'est pas présent dans le fichier.\n");
        }

        exit(0);
    }
    else
    {
        close(pipefd[0]); 

        char mot[MAX];
        printf("Entrez un mot à chercher : ");
        scanf("%s", mot);

       
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);

        FILE *f = fopen("fichier.txt", "r");
        if (!f)
        {
            perror("fichier.txt");
            exit(1);
        }

        char temp[MAX];
        int trouve = 0;

        while (fscanf(f, "%s", temp) != EOF)
        {
            if (strcmp(temp, mot) == 0)
            {
                trouve = 1;
                break;
            }
        }
        fclose(f);

      
        printf("%d\n", trouve);

        wait(NULL);
    }

    return 0;
}