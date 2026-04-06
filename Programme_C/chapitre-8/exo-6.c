#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 54322
#define MAX 10
#define BUF 256

int clients[MAX];
int count = 0;
int can_speak = -1;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char *msg, int sender)
{
    for(int i = 0; i < count; i++)
    {
        if(i != sender)
        {
            send(clients[i], msg, strlen(msg), 0);
        }
    }
}

void *handle(void *arg)
{
    int idx = *(int*)arg;
    free(arg);

    char buf[BUF];
    char ip[INET_ADDRSTRLEN];
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);

    getpeername(clients[idx], (struct sockaddr*)&addr, &len);
    inet_ntop(AF_INET, &addr.sin_addr, ip, sizeof(ip));

    while(1)
    {

        int n = recv(clients[idx], buf, BUF-1, 0);
        if(n <= 0)
        {
            break;
        }
        buf[n] = 0;
          
        pthread_mutex_lock(&lock);

        if(can_speak == -1)
        {
            can_speak = idx;
        }

        if(can_speak == idx)
        {
            char msg[BUF + 50];
            sprintf(msg, "%s: %s", ip, buf);
            broadcast(msg, idx);
            can_speak = -1;
        }

        pthread_mutex_unlock(&lock);
    }

    close(clients[idx]);
    return NULL;
}

int main()
{
    int sock;
    int s;
    struct sockaddr_in server;
    struct sockaddr_in client;
    socklen_t clilen = sizeof(client);
    pthread_t tid;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if(bind(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
    {
        perror("bind() : ");
        exit(1);
    }

    listen(sock, MAX);
    printf("Serveur en ecoute sur le port %d\n", PORT);

    while(1)
    {
        s = accept(sock, (struct sockaddr*)&client, &clilen);
        if(s < 0)
        {
            perror("accept");
            continue;
        }

        pthread_mutex_lock(&lock);

        clients[count] = s;
        int *pidx = malloc(sizeof(int));
        *pidx = count++;
        
        pthread_mutex_unlock(&lock);

        pthread_create(&tid, NULL, handle, pidx);
        pthread_detach(tid);
    }

    close(sock);
    return 0;
}