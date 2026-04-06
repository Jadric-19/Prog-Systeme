/*Écrire un programme qui crée un tube, crée un processus fils,
puis, dans le fils, lance par execv un autre programme, appelé programme fils. Le programme
père transmets les descripteurs de tubes au programmes fils en argument, et transmet un
message au fils par le tube. Le programme fils affiche le message.*/

//FILS

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE 100

int main(int argc, char *argv[]) 
{
    if (argc != 2) 
    {
        printf("Usage: %s <descripteur tube>\n", argv[0]);
        return 1;
    }

    int fd = atoi(argv[1]); 
    char buffer[TAILLE];

    
    read(fd, buffer, TAILLE);
    close(fd);

    printf("Message reçu : %s\n", buffer);

    return 0;
}