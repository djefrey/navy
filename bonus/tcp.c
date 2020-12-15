/*
** EPITECH PROJECT, 2020
** navy
** File description:
** tcp
*/

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "my.h"
#include "network.h"

static int setup_client_conn(int serv_sock)
{
    int csock;
    struct sockaddr_in csin;
    unsigned int sinsize = sizeof csin;

    my_putstr("Waiting enemy's connection...\n");
    csock = accept(serv_sock, (struct sockaddr*) &csin, &sinsize);
    if(csock == -1) {
        perror("Cannot accept connection");
        exit(84);
    }
    return (csock);
}

static void setup_host(int sock)
{
    struct sockaddr_in sin;

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    if (bind (sock, (struct sockaddr*) &sin, sizeof sin) == -1) {
        perror("Cannot bind socket");
        exit(84);
    }
    if (listen(sock, 1) == -1) {
        perror("Listenning to connections failed");
        exit(84);
    }
}

static void setup_client(char *ip, int sock)
{
    struct hostent *host;
    struct sockaddr_in sin;

    host = gethostbyname(ip);
    if (host == NULL) {
        perror("Unknown host");
        exit(84);
    }
    sin.sin_addr = *(struct in_addr*) host->h_addr;
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;
    if (connect(sock,(struct sockaddr*) &sin, sizeof(struct sockaddr)) == -1) {
        perror("Cannot connect to host");
        exit(84);
    }
}

int init_tcp(char *ip, int *serv_sock)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if(sock == -1) {
        perror("socket()");
        exit(84);
    }
    if (ip == NULL) {
        *serv_sock = sock;
        setup_host(sock);
        sock = setup_client_conn(*serv_sock);
    } else
        setup_client(ip, sock);
    return (sock);
}
