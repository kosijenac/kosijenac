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

void put_city(int sock)
{
    char grad[GRAD_SIZE], opis[OPIS_SIZE], msg[GRAD_SIZE + OPIS_SIZE + 10];
    int temp;

    printf("Unesite naziv grada (bez razmaka): ");
    scanf("%s", grad);
    printf("Unesite temperaturu u tom gradu (cijeli broj): ");
    scanf("%d", &temp);
    printf("Unesite opis prognoze u tom gradu (bez razmaka): ");
    scanf("%s", opis);

    sprintf(msg, "%s %d %s", grad, htonl(temp), opis);
    posaljiPoruku(sock, PUT_CITY, msg);

    int vrsta;
    char *resp = (char *)malloc(100);
    handle_response_macro(sock, vrsta, resp);

    free(resp);
}

void farewell(int sock)
{
    posaljiPoruku(sock, BYE, "...and may we meet again someday, old friend");
    int vrsta;
    char *resp = (char *)malloc(20);
    handle_response_macro(sock, vrsta, resp);
    free(resp);
}

int main(int argc, char **argv)
{
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        perror_and_return("socket");
    struct sockaddr_in servAddr;
    if (inet_aton(ADDR, &servAddr.sin_addr) == 0)
    {
        herror("inet_aton");
        return -1;
    }
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(PORT);
    memset(servAddr.sin_zero, '\0', 8);
    if (connect(sock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
        perror_and_return("connect");

    int bye = 0;
    while (!bye)
    {
        printf("\nOdaberite opciju:\n1. dodavanje/azuriranje prognoze\n5. izlaz iz programa\n>>> ");
        int odabir;
        if (scanf("%d", &odabir) < 1)
            continue;
        switch (odabir)
        {
        case PUT_CITY:
            put_city(sock);
            break;
        case BYE:
            farewell(sock);
            bye = 1;
            break;
        default:
            printf("To nije dozvoljen odabir!\n");
        }
    }
    if (close(sock) == -1)
        perror_and_return("close");
    return 0;
}