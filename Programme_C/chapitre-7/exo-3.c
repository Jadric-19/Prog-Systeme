/*Écrire un programme qui crée 5 processus fils qui font une boucle while
1. Le processus père proposera dans une boucle sans fin un menu à l’utilisateur :
• Endormir un fils ;
• Réveiller un fils ;
• Terminer un fils ;*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#define N 5

pid_t pids[N];  // tableau pour stocker les PID des fils

//Gestionnaire fils
void gestionnaire_fils(int sig) 
{
    switch(sig) 
    {
        case SIGUSR1 :
            printf("Fils %d: je suis réveillé !\n", getpid()) ;
            break ;
        case SIGUSR2 :
            printf("Fils %d: je m'endors...\n", getpid());
            pause() ;  // attends un signal pour se réveiller
            break ;
        case SIGTERM :
            printf("Fils %d: je suis tué !\n", getpid());
            exit(0) ;
    }
}

//Gestionnaire  pere
void gestionnaire_pere(int sig) 
{
    if(sig == SIGTERM) 
    {
        printf("Père %d: je suis tué !\n", getpid()) ;
        exit(0) ;
    }
}

// Creation de fils leurs PID dans pids[] 
void creer_fils() 
{
    int i = 0 ;
    pid_t pid ;
    for( i = 0; i < N; i++) 
    {
        pid = fork();
        if(pid < 0) 
         {
            perror("fork");
            exit(1);
         }
        if(pid == 0) 
         {
       
            struct sigaction fils_action ;
            fils_action.sa_handler = gestionnaire_fils ;
            sigemptyset(&fils_action.sa_mask);
            fils_action.sa_flags = 0;
            sigaction(SIGUSR1 , &fils_action , NULL);
            sigaction(SIGUSR2 , &fils_action  , NULL);
            sigaction(SIGTERM , &fils_action , NULL);

            int j = 0;
            while(1) 
             {
                printf("Fils %d: boucle %d\n", getpid(), j++);
                fflush(stdout);
                sleep(2);
             }
            exit(0);
         }
        else 
        {   
            pids[i] = pid ;
        }
    }
}

// MENU
int menu() 
{
    int choix ;
    printf("\n -------------MENU :-------------\n");
    printf("1 - Endormir un fils \n") ;
    printf("2 - Réveiller un fils \n") ;
    printf("3 - Terminer un fils \n") ;
    printf("4 - Terminer le père \n") ;
    printf("==>Votre choix: ") ;
    scanf("%d", &choix) ;
    return choix;
}

// Traite le choix
void traiter_choix(int choix) 
{
    int fils_num ;
    if(choix >= 1 && choix <= 3) 
    {
        printf("Numéro du fils (1-%d): ", N);
        scanf("%d", &fils_num);
        if(fils_num < 1 || fils_num > N) 
        {
            printf("Fils invalide !\n");
            return;
        }
    }

    switch(choix) 
    {
        case 1:  
            kill(pids[fils_num - 1], SIGUSR2);
            break;
        case 2:  
            kill(pids[fils_num - 1], SIGUSR1);
            break;
        case 3:  
            kill(pids[fils_num - 1], SIGTERM);
            break;
        case 4:  
            kill(getpid(), SIGTERM);
            exit(0) ;
            break;
        default:
            printf("Choix invalide !\n");
    }
}

int main() 
{
    
    struct sigaction sa_pere;
    sa_pere.sa_handler = gestionnaire_pere;
    sigemptyset(&sa_pere.sa_mask);
    sa_pere.sa_flags = 0;
    sigaction(SIGTERM, &sa_pere, NULL);

    // Creation des fils
    creer_fils();

    // Boucle menu pere
    while(1) 
    {
        int choix = menu();
        traiter_choix(choix);
    }

    return 0;
}