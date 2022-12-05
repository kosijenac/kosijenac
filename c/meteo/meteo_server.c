#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

struct Prognoza
{
    char grad[20];
    int temp;
    char stanje[20];
};

struct Meteorolog
{
    char username[8];
    char password[8];
};

struct Prognoza prognoze[100];
struct Meteorolog ovlastene_osobe[100];
