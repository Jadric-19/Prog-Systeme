/*Écrire un programme qui crée un tube, crée un processus fils,
puis, dans le fils, lance par execv un autre programme, appelé programme fils. Le programme
père transmets les descripteurs de tubes au programmes fils en argument, et transmet un
message au fils par le tube. Le programme fils affiche le message.mais en passant les descripteurs de tube
comme variables d’environnement.*/

//FILS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE 100

int main() 
{
    char *tube_str = getenv("TUBE_FD");
    
    if (!tube_str) 
    {
        fprintf(stderr, "Variable TUBE_FD non definie !\n");
        return 1;
    }

    int fd = atoi(tube_str); 

    char buffer[TAILLE];
    read(fd, buffer, TAILLE); 
    close(fd);

    printf("Message recu : %s\n", buffer);

    return 0;
}