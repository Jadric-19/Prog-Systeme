/*Ecrire un programme qui crée un fils qui fait un calcul sans fin. Le processus
père propose alors un menu :
• Lorsque l’utilisateur appuie sur la touche 's', le processus père endort son fils.
• Lorsque l’utilisateur appuie sur la touche 'r', le processus père redémare son fils.
• Lorsque l’utili*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>

void gestionnaire(int numero)
{
     switch(numero)
     {
        case SIGUSR1:
             printf("\n---------- REDEMMARAGE DU FILS ---------\n") ;
             
             break ;
        case SIGUSR2:
             printf("\n---------- FILS ENDORMIE------------\n") ;
             pause() ;
             break ;
     }   
}

int main()
{
   
    pid_t pid ;
    char rep ;

    
    
    pid = fork() ;

    if( pid == -1 )
     {
        printf("\n---------- ERREUR : FORK()-------------------\n") ;
        exit(0) ;
     }

    if( pid == 0 )
     {
         struct sigaction action ;
         action.sa_handler = gestionnaire ;
         sigemptyset(&action.sa_mask);
         action.sa_flags = 0 ;
         if(sigaction(SIGUSR1 , &action , NULL) != 0  || sigaction(SIGUSR2 , &action , NULL) != 0)
          {
              printf("\n-------ERREUR : SIGNAL-------------\n") ;
              exit(0) ;
          }
         int i = 1 , j = 0  ;
         while(i)
           {
                printf("\n---- %d ----\n" , j++) ;
                sleep(2) ;
           }
     }
    else if( pid > 0 )
     {
        while(1)
         {
            printf("\n==> (s) pour endormir le fils , (r) pour le redemmer , (q) pour le tuer : ") ;
            scanf(" %c" , &rep) ;

            if(rep == 's')
            {
                 kill(pid , SIGUSR2) ;
            }
            else if(rep == 'r')
             {
                 kill(pid , SIGUSR1) ;
             }
            else if(rep == 'q')
            {
                 kill(pid , SIGKILL) ;
                 break ;
                 //return 1 ;
            }
            else
            {
                 printf("\n--- SIGNAL NON REPERTORIER ----\n") ;
            }
       }
    }
    
    return 0 ;

}