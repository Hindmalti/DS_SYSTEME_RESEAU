#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "mario.h"


//Etape 1 : Serveur UDP sur le port de Peach pour lire son message
//Etape 2 : Envoie message TCP à Luigi pour transferer le message de Peach
//Etape 3 : Reception de la réponse

struct sockaddr_in peach_addr;

int ecoutePeach()
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));

    
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PEACH_PORT);

    // Bind socket 
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    //Reception
    int n;
    socklen_t len = sizeof(peach_addr);
    //Recoit le message de Peach

    n = recvfrom(sockfd, (char *)buffer, MAXLINE, 0, (struct sockaddr *) &peach_addr, &len);
    buffer[n] = '\0';
    printf("From Peach : %s\n", buffer);

    //Etape2 : Envoyer le buffer en TCP
    if (envoieLuigi(buffer, strlen(buffer)) != 0)
    {
        perror("Erreur lors de l'envoie à Luigi\n");
    }
    return 0;
}

int envoieLuigi(char *payload, int taille)
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buffer[MAXLINE];

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(LUIGI_PORT);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
        printf("connection with the server failed...\n");
        exit(0);
    }
    else
        printf("connected to the server..\n");

    //Envoie à Luigi
    printf("Envoie du message à Luigi : %s\n", payload);
    if(write(sockfd, payload, taille) < 0){
        perror("[envoieLuigi]write");
    }

    bzero(payload, taille);

    //Récupère la réponse de Luigi
    if(read(sockfd, buffer, sizeof(buffer))<0){
        perror("[envoieLuigi]read");
    }
    printf("From Luigi : %s\n", buffer);

    //Renvoie à Peach
    envoiePeach(buffer, sizeof(buffer));

    // close the socket
    close(sockfd);
    return 0;
}

int envoiePeach(char *payload, int taille)
{
    int sockfd;

    // Creation du file descriptor de la socket 
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    printf("Envoie du message :  %s à Peach\n", payload);

    if(sendto(sockfd, (const char *)payload, taille, 0, (const struct sockaddr *) &peach_addr, sizeof(peach_addr))<0){
        perror("[envoiePeach]send\n");
    }

    close(sockfd);
    return 0;
}

int main()
{
    ecoutePeach();
    return 0;
}