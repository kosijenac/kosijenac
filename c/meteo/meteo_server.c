#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "meteo_protocol.h"

struct Prognoza
{
    char grad[GRAD_SIZE];
    int temp;
    char opis[OPIS_SIZE];
};

struct Prognoza prognoze[MAX_PROGNOZA];
int brProg = 0;

void put_city(int sock, char *msg)
{
    char grad[GRAD_SIZE], opis[OPIS_SIZE];
    int temp_n, prog_ix = -1;
    if (sscanf(msg, "%s %d %s", grad, &temp_n, opis) < 3)
    {
        posaljiPoruku(sock, RESPONSE, "Format poruke: IME_GRADA TEMPERATURA OPIS_PROGNOZE\n");
        return;
    }
    int temp = ntohl(temp_n);
    for (int i = 0; i < brProg; i++)
        if (strcmp(prognoze[i].grad, grad) == 0)
            prog_ix = i;
    if (prog_ix == -1)
    {
        if (brProg == MAX_PROGNOZA)
        {
            posaljiPoruku(sock, RESPONSE, "Dostignut maksimalan broj prognoza.\n");
            return;
        }
        struct Prognoza prog;
        strcpy(prog.grad, grad);
        strcpy(prog.opis, opis);
        prog.temp = temp;
        prognoze[brProg++] = prog;
    }
    else
    {
        strcpy(prognoze[prog_ix].opis, opis);
        prognoze[prog_ix].temp = temp;
    }
    posaljiPoruku(sock, RESPONSE, "OK");
}

void get_city(int sock, char *msg)
{
    // naziv grada je upravo jednak msg
    int prog_ix = -1;
    for (int i = 0; i < brProg; i++)
        if (strcmp(prognoze[i].grad, msg) == 0)
            prog_ix = i;
    if (prog_ix == -1)
        posaljiPoruku(sock, RESPONSE, "Grad ne postoji ili za nj nije poznata prognoza.\n");
    else
    {
        posaljiPoruku(sock, RESPONSE, "OK");
        char resp[GRAD_SIZE + OPIS_SIZE + 5];
        sprintf(resp, "%d %s", htonl(prognoze[prog_ix].temp), prognoze[prog_ix].opis);
        posaljiPoruku(sock, GET_CITY_R, resp);
    }
}

void handleClient(int sock)
{
    int vrsta, bye = 0;
    char *msg = (char *)malloc(GRAD_SIZE + OPIS_SIZE + 10);
    while (!bye)
    {
        if (primiPoruku(sock, &vrsta, &msg) != OK)
        {
            printf("Error at socket %d!\n", sock);
            bye++;
            continue;
        }
        switch (vrsta)
        {
        case PUT_CITY:
            put_city(sock, msg);
            break;
        case GET_CITY:
            get_city(sock, msg);
            break;
        case BYE:
            posaljiPoruku(sock, RESPONSE, "OK");
            bye++;
            break;
        default:
            posaljiPoruku(sock, RESPONSE, "Vrsta poruke nije valjana!\n");
        }
    }
    free(msg);
}

int main(int argc, char **argv)
{
    int listenSock = socket(PF_INET, SOCK_STREAM, 0);
    if (listenSock == -1)
        perror_and_return("socket");
    struct sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    servAddr.sin_addr.s_addr = INADDR_ANY;
    memset(servAddr.sin_zero, '\0', 8);

    if (bind(listenSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
        perror_and_return("bind");
    if (listen(listenSock, 32) == -1)
        perror_and_return("listen");

    while (1)
    {
        struct sockaddr_in clAddr;
        int lenAddr = sizeof(clAddr);

        int commSock = accept(listenSock, (struct sockaddr *)&clAddr, &lenAddr);
        if (commSock == -1)
            perror("accept");
        printf("Accepted connection from %s [port=%d, sock=%d].\n",
               inet_ntoa(clAddr.sin_addr), ntohs(clAddr.sin_port), commSock);

        handleClient(commSock);

        if (close(commSock) == -1)
            perror("close");
        printf("Closed connection from %s [port=%d, sock=%d].\n",
               inet_ntoa(clAddr.sin_addr), ntohs(clAddr.sin_port), commSock);
    }
}