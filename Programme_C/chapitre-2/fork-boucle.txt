#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{
    pid_t pid;
    int i;

    for (i = 0; i < 5; i++) 
     {
        pid = fork(); 

        if (pid < 0) 
         {
      
            perror("fork");
            return 1;
         }

        if (pid == 0) 
         {
            
            printf("Je suis le Fils %d , PID=%d, PID du père=%d\n", i+1, getpid(), getppid());
            break; 
         }
      
     }

 
    printf("Processus PID=%d termine sa boucle.\n", getpid());

    return 0 ;
    
}