#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define BUF 256
#define TRUE 1

int main()
{
    int serv, cli[2], n;
    struct sockaddr_in addr;
    char buffer[BUF];

    serv = socket(AF_INET, SOCK_STREAM, 0);
    if(serv < 0){ perror("socket"); exit(1); }

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if(bind(serv, (struct sockaddr*)&addr, sizeof(addr)) < 0){ perror("bind"); exit(1); }
    listen(serv, 2);

    printf("Attente de 2 clients...\n");
    cli[0] = accept(serv, NULL, NULL);
    cli[1] = accept(serv, NULL, NULL);
    printf("2 clients connectés.\n");

    while(TRUE)
    {
        memset(buffer, 0, BUF);
        send(cli[0], "Saisissez la phrase : ", 23, 0);
        n = recv(cli[0], buffer, BUF, 0);
        if(n <= 0) break;
        send(cli[1], "L'autre client dit : ", 21, 0);
        send(cli[1], buffer, n, 0);

        memset(buffer, 0, BUF);
        send(cli[1], "Saisissez la phrase : ", 23, 0);
        n = recv(cli[1], buffer, BUF, 0);
        if(n <= 0) break;
        send(cli[0], "L'autre client dit : ", 21, 0);
        send(cli[0], buffer, n, 0);
    }

    close(cli[0]);
    close(cli[1]);
    close(serv);
    return 0;
}