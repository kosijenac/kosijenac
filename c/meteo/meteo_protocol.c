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

int posaljiPoruku(int sock, int vrstaPoruke, const char *poruka)
{
	int length = strlen(poruka);

	int sent, new_sent;
	int length_n = htonl(length);
	new_sent = send(sock, &length_n, sizeof(length_n), 0);
	if (new_sent != sizeof(length_n))
		return NE;

	int vrstaPoruke_n = htonl(vrstaPoruke);
	new_sent = send(sock, &vrstaPoruke_n, sizeof(vrstaPoruke_n), 0);
	if (new_sent != sizeof(vrstaPoruke_n))
		return NE;

	sent = 0;
	while (sent != length)
	{
		new_sent = send(sock, poruka + sent, length - sent, 0);

		if (new_sent == -1 || new_sent == 0)
			return NE;
		sent += new_sent;
	}

	return OK;
}

int primiPoruku(int sock, int *vrstaPoruke, char **poruka)
{
	int recd, new_recd;
	int length_n, length;
	new_recd = recv(sock, &length_n, sizeof(length_n), 0);
	if (new_recd != sizeof(length_n))
		return NE;
	length = ntohl(length_n);

	int vrstaPoruke_n;
	new_recd = recv(sock, &vrstaPoruke_n, sizeof(vrstaPoruke_n), 0);
	if (new_recd != sizeof(new_recd))
		return NE;
	*vrstaPoruke = ntohl(vrstaPoruke_n);

	*poruka = (char *)malloc((length + 1) * sizeof(char));

	recd = 0;
	while (recd != length)
	{
		new_recd = recv(sock, *poruka + recd, length - recd, 0);

		if (new_recd == -1 || new_recd == 0)
			return NE;
		recd += new_recd;
	}

	(*poruka)[length] = '\0';

	return OK;
}
