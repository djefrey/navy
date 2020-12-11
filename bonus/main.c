/*
** EPITECH PROJECT, 2020
** navy
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "my.h"
#include "navy.h"
#include "network.h"

int main(int ac, char *av[])
{
    int serv_sock = 0;
    int sock;
    char host = ac == 2;
    char my_board[8][8];
    char en_board[8][8];

    if (ac < 2 || ac > 3 ||
    init_board(my_board, en_board, host ? av[1] : av[2]))
        return (84);
    if (ac == 3) {
        sock = init_tcp(av[1], NULL);
    } else if (ac == 2)
        sock = init_tcp(NULL, &serv_sock);
    else
        return (84);
    while (play_turn(host, sock, my_board, en_board));
    if (serv_sock)
        close(serv_sock);
    close(sock);
    return (0);
}