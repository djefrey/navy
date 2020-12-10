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

static char invalid_line(char *line, ssize_t read)
{
    int size;
    int len;
    int start_pos;
    int end_pos;

    if (read != 7 || (line[0] < '2' || line[0] > '5'))
        return (1);
    else if (line[2] < 'A' || line[2] > 'H' || line[3] < '1' || line[3] > '8'
    || line[5] < 'A' || line[5] > 'H' || line[6] < '1' || line[6] > '8')
        return (1);
    size = line[0] - '0';
    start_pos = (line[2] - 'A') * 10 + (line[3] - '1');
    end_pos = (line[5] - 'A') * 10 + (line[6] - '1');
    len = ABS(end_pos - start_pos);
    if (len != size - 1 && len != (size - 1) * 10)
        return (1);
    return (0);
}

static char read_file(char *path, char *boats[4])
{
    FILE *file = fopen(path, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    if (file == NULL)
        return (1);
    for (int i = 0; i < 4; i++) {
        read = getline(&line, &len, file);
        if (read == 8) {
            line[7] = 0;
            read--;
        }
        if (invalid_line(line, read))
            return (1);
        boats[i] = line;
        line = NULL;
    }
    return (0);
}

static char init_board(char my_board[8][8], char en_board[8][8], char *file)
{
    char *boats[4] = {NULL, NULL, NULL, NULL};

    if (read_file(file, boats)) {
        for (int i = 0; i < 4; i++) {
            if (boats[i] != NULL)
                free(boats[i]);
        }
        return (1);
    }
    setup_board(my_board);
    setup_board(en_board);
    set_boats(my_board, boats);
    for (int i = 0; i < 4; i++)
        free(boats[i]);
    return (0);
}

void print_board(char board[8][8])
{
    my_putstr(" |A B C D E F G H\n");
    my_putstr("-+---------------\n");
    for (int y = 0; y < 8; y++) {
        my_printf("%i|", y + 1);
        for (int x = 0; x < 8; x++) {
            my_putchar(board[x][y]);
            my_putchar(x == 7 ? '\n' : ' ');
        }
    }
}

char end_game(char end)
{
    if (end == -1) {
        my_putstr("\nEnemy won\n");
        return (1);
    } else if (end == 1) {
        my_putstr("\nI won\n");
        return (1);
    } else
        return (0);
}

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