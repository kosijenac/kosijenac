#ifndef __METEO_PROTOCOL_H_

#define __METEO_PROTOCOL_H_

#define PUT_CITY 1
#define GET_CITY 2
#define GET_CITY_R 3
#define RESPONSE 4
#define BYE 5

#define OK 1
#define NE 0

#define GRAD_SIZE 30
#define OPIS_SIZE 30
#define MAX_PROGNOZA 100
#define PORT 8036
#define ADDR "194.36.45.89"

int primiPoruku(int sock, int *vrstaPoruke, char **poruka);
int posaljiPoruku(int sock, int vrstaPoruke, const char *poruka);

#define perror_and_return(x) \
    {                        \
        perror(x);           \
        return -1;           \
    }

#define handle_response_macro(sock, vrsta, resp, TYPE)         \
    if (primiPoruku(sock, &vrsta, &resp) != OK)                \
    {                                                          \
        printf("Error at socket %d!\n", sock);                 \
        return;                                                \
    }                                                          \
    if (vrsta != TYPE)                                         \
        printf("Server nije vratio dobar format odgovora!\n"); \
    if (strcmp(resp, "OK"))                                    \
        printf("Server javlja sljedecu gresku: ");             \
    printf("%s\n", resp);

#endif