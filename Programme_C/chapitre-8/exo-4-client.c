#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF 4096

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: %s <IP> <repertoire>\n", argv[0]);
        return 1;
    }

    char tmpfile[256];
    snprintf(tmpfile, sizeof(tmpfile), "/tmp/send_archive.tar");

    char cmd[512];
    snprintf(cmd, sizeof(cmd), "tar -cf %s -C %s .", tmpfile, argv[2]);
    if(system(cmd) != 0)
    {
        printf("Erreur ceeation archive\n");
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

    FILE *f = fopen(tmpfile, "rb");
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

    printf("Archive envoye.\n");
    return 0;
}