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

void get_city(int sock)
{
    char grad[GRAD_SIZE];

    printf("Unesite naziv grada (bez razmaka): ");
    scanf("%s", grad);

    posaljiPoruku(sock, GET_CITY, grad);

    int vrsta;
    char *resp = (char *)malloc(100);
    handle_response_macro(sock, vrsta, resp);
    if (strcmp(resp, "OK"))
        return;

    if (primiPoruku(sock, &vrsta, &resp) != OK)
        return;
    if (vrsta != GET_CITY_R)
        printf("Server nije vratio dobar format odgovora!\n");
    int temp_n;
    char opis[OPIS_SIZE];
    if (sscanf(resp, "%d %s", &temp_n, opis) < 2)
        return;
    printf("%s: %d°C, %s\n", grad, ntohl(temp_n), opis);

    free(resp);
}

void farewell(int sock)
{
    posaljiPoruku(sock, BYE, "...and may we never meet again");
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
        printf("\nOdaberite opciju:\n2. pregled prognoze\n5. izlaz iz programa\n>>> ");
        int odabir;
        if (scanf("%d", &odabir) < 1)
            break;
        switch (odabir)
        {
        case GET_CITY:
            get_city(sock);
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