/*Écrire un programme qui crée un tube, crée un processus fils,
puis, dans le fils, lance par execv un autre programme, appelé programme fils. Le programme
père transmets les descripteurs de tubes au programmes fils en argument, et transmet un
message au fils par le tube. Le programme fils affiche le message.mais en passant les descripteurs de tube
comme variables d’environnement.*/

//PERE


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() 
{
    int tube[2];

    if (pipe(tube) == -1) 
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
        close(tube[1]);

        char tube_fd[10];
        sprintf(tube_fd, "%d", tube[0]);

        char env_var[20];
        snprintf(env_var, sizeof(env_var), "TUBE_FD=%s", tube_fd);

        char *envp[] = {env_var, NULL};

        char *args[] = {"./programme_fils_env", NULL} ;
        execve(args[0], args, envp);

        perror("execve"); 
        exit(1);
    } 
    else 
    { 
        close(tube[0]); 

        
        char message[] = "Bonjour via variable d'environnement !";
  
        write(tube[1], message, strlen(message)+1);
        close(tube[1]); 

        wait(NULL); 
    }

    return 0;
}