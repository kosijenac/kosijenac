#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Program treba primiti jedan (1) ulazni parametar!\n");
        return argc - 2;
    }
    struct hostent *host;
    struct in_addr binaryIP;
    if (inet_aton(argv[1], &binaryIP))
    {
        host = gethostbyaddr(&binaryIP, sizeof(binaryIP), AF_INET);
        if (!host)
        {
            herror("gethostbyaddr");
            return -3;
        }
    }
    else
    {
        host = gethostbyname(argv[1]);
        if (!host)
        {
            herror("gethostbyname");
            return -4;
        }
    }
    printf("Nazivi: \n");
    puts(host->h_name);
    for (int i = 0; host->h_aliases[i]; i++)
        puts(host->h_aliases[i]);
    printf("\nAdrese: \n");
    for (int i = 0; host->h_addr_list[i]; i++)
        puts(inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    return 0;
}