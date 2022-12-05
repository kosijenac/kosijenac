#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

void posalji(int sock, char *poruka, int duljinaPoruke)
{
    int poslano = 0;   // broj do sada poslanih byte-ova
    int poslanoZadnje; // koliko je poslano u zadnjem send

    while (poslano != duljinaPoruke)
    {
        poslanoZadnje = send(
            sock,
            poruka + poslano,
            duljinaPoruke - poslano,
            0);

        if (poslanoZadnje == -1)
        {
            perror("send");
            break;
        }
        else
            poslano += poslanoZadnje;
    }
}

void ucitajWebStranicu(int sock, char *buffer, int bufferSize)
{
    // prima podatke sve dok server ne prekine konekciju
    // problem -- treba osigurati dovoljno veliki buffer...ignoriramo :)

    // recv...
    int primljeno = 0; // koliko smo byte-ova ukupno primili
    int novoprimljeno; // koliko je primljeno u zadnjem recv

    while (1)
    {
        novoprimljeno = recv(
            sock,
            buffer + primljeno,
            bufferSize - 1 - primljeno,
            0);

        if (novoprimljeno == -1)
        {
            perror("recv");
            break;
        }
        else if (novoprimljeno == 0)
            break; // ucitali smo cijelu web-stranicu
        else
            primljeno += novoprimljeno;
    }

    buffer[primljeno] = '\0';
}

void nacrtajWebStranicu(char *webStranica)
{
    int unutarManje = 0, pocetakBody, krajBody;
    char *temp;

    if ((temp = strstr(webStranica, "<body")) != NULL)
        pocetakBody = temp - webStranica;
    else if ((temp = strstr(webStranica, "<BODY")) != NULL)
        pocetakBody = temp - webStranica;
    else
        pocetakBody = 0; // ako nema body...ispisuj sve

    if ((temp = strstr(webStranica, "</body>")) != NULL)
        krajBody = temp - webStranica;
    else if ((temp = strstr(webStranica, "</BODY>")) != NULL)
        krajBody = temp - webStranica;
    else
        krajBody = strlen(webStranica); // ako nema body...ispisuj sve

    int i;
    for (i = pocetakBody; i < krajBody; ++i)
        if (webStranica[i] == '<')
            unutarManje = 1;
        else if (webStranica[i] == '>')
            unutarManje = 0;
        else if (!unutarManje)
            printf("%c", webStranica[i]);

    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 2 && argc != 3)
    {
        printf("Upotreba: %s host-name (direktorij)\n", argv[0]);
        printf("Na primjer:\n");
        printf("\t%s degiorgi.math.hr\n", argv[0]);
        printf("\t%s www.bug.hr\n", argv[0]);
        printf("\t%s web.math.pmf.unizg.hr /nastava/mreze/index.php\n", argv[0]);
        printf("\t%s degiorgi.math.hr /forum/index.php\n", argv[0]);

        exit(0);
    }

    char *poddirektorij = "/";
    if (argc == 3)
        poddirektorij = argv[2];

    // socket...
    int mojSocket = socket(PF_INET, SOCK_STREAM, 0);
    if (mojSocket == -1)
        perror("socket");

    // connect...
    struct hostent *hostInfo = gethostbyname(argv[1]);
    if (hostInfo == NULL)
    {
        herror("gethostbyname");
        printf("%s nije dobra adresa!\n", argv[1]);
        exit(0);
    }

    struct sockaddr_in adresaServera;

    adresaServera.sin_family = AF_INET;
    adresaServera.sin_port = htons(80);
    adresaServera.sin_addr = *((struct in_addr *)hostInfo->h_addr);
    memset(adresaServera.sin_zero, '\0', 8);

    if (connect(
            mojSocket,
            (struct sockaddr *)&adresaServera,
            sizeof(adresaServera)) == -1)
        perror("connect");

    char zahtjevWebServeru[100];
    sprintf(zahtjevWebServeru, "GET %s HTTP/1.0\n\n", poddirektorij);
    posalji(mojSocket, zahtjevWebServeru, strlen(zahtjevWebServeru));

    char webStranica[20000]; // valjda je 20kB dosta za web-stranicu :)
    ucitajWebStranicu(mojSocket, webStranica, sizeof(webStranica));

    // close...
    if (close(mojSocket) == -1)
        perror("close");

    nacrtajWebStranicu(webStranica);

    return 0;
}
