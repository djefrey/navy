/*
** EPITECH PROJECT, 2020
** navy
** File description:
** main
*/

#include <stdlib.h>
#include "my.h"
#include "navy.h"
#include "network.h"

static void init_board(char my_board[8][8], char en_board[8][8], char *file)
{
    char *boats[4] = {"2:C1:C2", "3:D4:F4", "4:B5:B8", "5:D7:H7"};
    setup_board(my_board);
    setup_board(en_board);
    set_boats(my_board, boats);
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
    int enemy_pid;
    char host = ac == 1;
    char my_board[8][8];
    char en_board[8][8];

    if (ac == 2) {
        enemy_pid = my_getnbr(av[1]);
        init_signals(enemy_pid);
    } else
        enemy_pid = init_signals(-1);
    init_board(my_board, en_board, NULL);
    while (play_turn(host, enemy_pid, my_board, en_board)) {}
    return (0);
}