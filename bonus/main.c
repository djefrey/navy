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
#include "bonus.h"
#include "network.h"

int main(int ac, char *av[])
{
    int serv_sock = 0;
    int sock;
    char host = ac == 2;
    navy_t *navy = malloc(sizeof(navy_t));

    if (navy == NULL)
        return (84);
    if (ac < 2 || ac > 3 ||
    init_board(navy->my_board, navy->en_board, host ? av[1] : av[2]))
        return (84);
    if (ac == 3) {
        sock = init_tcp(av[1], NULL);
    } else if (ac == 2)
        sock = init_tcp(NULL, &serv_sock);
    else
        return (84);
    init_windows(navy);
    while (play_turn(host, sock, navy));
    getch();
    endwin();
    if (serv_sock)
        close(serv_sock);
    close(sock);
    free(navy);
    return (0);
}