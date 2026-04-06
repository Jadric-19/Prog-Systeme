#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 9090
#define BUFFER_SIZE 256


int ip_autorise(const char *ip, char *nom)
{
    FILE *f = fopen("add_autoris.txt", "r");
    if (!f)
      return 0;

    char ligne[100], ip_f[50], nom_f[50];
    while (fgets(ligne, sizeof(ligne), f))
    {
        if (sscanf(ligne, "%s %s", ip_f, nom_f) == 2)
        {
            if (strcmp(ip, ip_f) == 0)
            {
                strcpy(nom, nom_f);
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);
    return 0;
}

int main()
{
    int sockfd, newsock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Erreur socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Erreur bind() : ");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    listen(sockfd, 5);
    printf("Serveur en attente de connexion sur le port %d...\n", PORT);

    while (1)
    {
        newsock = accept(sockfd, (struct sockaddr*)&client_addr, &addr_len);
        if (newsock < 0)
        {
            perror("Erreur accept() : ");
            continue;
        }

        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);

        char nom[50];
        if (ip_autorise(client_ip, nom))
        {
            sprintf(buffer, "Bienvenue %s !\n", nom);
        }
        else
        {
            sprintf(buffer, "IP non autorisée.\n");
        }

        write(newsock, buffer, strlen(buffer));
        close(newsock);
    }

    close(sockfd);
    return 0;
}