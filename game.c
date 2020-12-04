/*
** EPITECH PROJECT, 2020
** navy
** File description:
** game
*/

#include <unistd.h>
#include "my.h"
#include "navy.h"
#include "network.h"

char check_lose(char my_board[8][8])
{
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            if (my_board[x][y] >= '2' && my_board[x][y] <= '5')
                return (0);
        }
    }
    return (1);
}

void ask_target(char buff[2])
{
    char valid = 0;

    while (!valid) {
        my_putstr("attack: ");
        read(0, buff, 2);
        valid = (buff[0] >= 'A' && buff[0] <= 'H'
        && buff[1] >= '1' && buff[1] <= '8');
        if (!valid)
            my_putstr("wrong position\n");
    }
}

char my_turn(int enemy_pid, char en_board[8][8])
{
    char buff[2];
    int res;
    int pos;

    ask_target(buff);
    pos = (buff[0] - 'A') * 10 + (buff[1] - '1');
    send_position(enemy_pid, buff);
    res = wait_for_result();
    my_printf("%s: %s\n", buff, (res & HIT_FLAG) ? "hit" : "miss");
    mark_pos(en_board, pos, (res & HIT_FLAG) > 0);
    if (res & WIN_FLAG) {
        end_game(1);
        return (1);
    } else
        return (0);
}

char en_turn(int enemy_pid, char my_board[8][8])
{
    int pos;
    int hit;
    char lose;

    pos = wait_for_position();
    hit = get_pos(my_board, pos);
    mark_pos(my_board, pos, hit);
    lose = check_lose(my_board);
    send_result(enemy_pid, hit, lose);
    if (lose) {
        end_game(-1);
        return (1);
    } else
        return (0);
}

int play_turn(char host, int enemy_pid,
char my_board[8][8], char en_board[8][8])
{
    my_putstr("\nmy positions:\n");
    print_board(my_board);
    my_putstr("\nenemy's positions:\n");
    print_board(en_board);
    my_putchar('\n');
    if (host) {
        if (my_turn(enemy_pid, en_board))
            return (0);
        my_putchar('\n');
        if (en_turn(enemy_pid, my_board))
            return (0);
    } else {
        if (en_turn(enemy_pid, my_board))
            return (0);
        my_putchar('\n');
        if (my_turn(enemy_pid, en_board))
            return (0);
    }
    return (1);
}
