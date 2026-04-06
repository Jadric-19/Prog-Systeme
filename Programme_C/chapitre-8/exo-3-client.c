#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF 1024

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <IP> <fichier>\n", argv[0]);
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_port = htons(54321);
    inet_pton(AF_INET, argv[1], &serv.sin_addr);

    if(connect(sock, (struct sockaddr*)&serv, sizeof(serv)) < 0)
    {
        perror("connect() : ");
        return 1;
    }

    FILE *f = fopen(argv[2], "r");

    if(!f)
    {
        perror("fopen() : ");
        return 1;
    }

    char buf[BUF];
    int n;
    while((n = fread(buf, 1, BUF, f)) > 0)
    {
        write(sock, buf, n);
    }

    fclose(f);
    close(sock);

    printf("Fichier envoye \n");
    return 0;
}