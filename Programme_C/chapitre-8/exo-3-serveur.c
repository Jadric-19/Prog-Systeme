#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 54321
#define BUF 1024

int main()
{
    int sockfd, newsock;
    struct sockaddr_in serv, cli;
    socklen_t clilen = sizeof(cli);
    char buf[BUF];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr*)&serv, sizeof(serv));
    listen(sockfd, 5);

    printf("Serveur en attente...\n");

    while(1)
    {
        newsock = accept(sockfd, (struct sockaddr*)&cli, &clilen);

        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &cli.sin_addr, ip, sizeof(ip));

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);

        char filename[256];
        snprintf(filename, sizeof(filename), "/tmp/%s_%04d_%02d_%02d.txt",
                 ip, tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday);

        FILE *f = fopen(filename, "w");

        if(!f)
        {
            perror("fopen");
            close(newsock);
            continue;
        }

        int n;
        while((n = read(newsock, buf, BUF)) > 0)
        {
            fwrite(buf, 1, n, f);
        }

        fclose(f);
        close(newsock);

        printf("Fichier recu de %s\n", ip);
    }

    close(sockfd);
    return 0;
}