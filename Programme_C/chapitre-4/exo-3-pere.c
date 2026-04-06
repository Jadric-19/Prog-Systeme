/*Écrire un programme qui crée un tube, crée un processus fils,
puis, dans le fils, lance par execv un autre programme, appelé programme fils. Le programme
père transmets les descripteurs de tubes au programmes fils en argument, et transmet un
message au fils par le tube. Le programme fils affiche le message.*/

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

        char *args[] = {"./programme_fils", tube_fd, NULL};
        execv(args[0], args);

        perror("execv");
        exit(1);
    } 
    else 
    { 
        
        close(tube[0]);
        
        char message[] = "Bonjour au fils !";
        
        write(tube[1], message, strlen(message)+1);
        close(tube[1]); 
        wait(NULL); 
    }

    return 0;
}