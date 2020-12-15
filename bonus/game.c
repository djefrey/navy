/*
** EPITECH PROJECT, 2020
** navy
** File description:
** game
*/

#include <unistd.h>
#include <ncurses.h>
#include "my.h"
#include "bonus.h"
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

void ask_target(navy_t *navy, char buff[2])
{
    unsigned char c;
    int pos = 0;

    while (1) {
        c = getch();
        switch (c) {
        case 10:
            if (pos == 2) {
                mvwaddch(navy->target_win, 1, 2, ' ');
                mvwaddch(navy->target_win, 1, 3, ' ');
                wrefresh(navy->target_win);
                return;
            }
            break;
        case 127:
            if (pos == 0)
                break;
            buff[pos] = 0;
            mvwaddch(navy->target_win, 1, 1 + pos, ' ');
            wrefresh(navy->target_win);
            pos -= 1;
            break;
        default:
            if ((c >= 'A' && c <= 'H' && pos == 0) ||
            (c >= '1' && c <= '8' && pos == 1)) {
                buff[pos] = c;
                mvwaddch(navy->target_win, 1, 2 + pos, c);
                pos += 1;
                wrefresh(navy->target_win);
            }
            break;
        }
    }
}

char my_turn(int sock, navy_t *navy)
{
    char buff[2] = {0, 0};
    int res;
    int pos;

    print_status("Your turn", 9);
    ask_target(navy, buff);
    pos = (buff[0] - 'A') * 10 + (buff[1] - '1');
    send_position(sock, buff);
    res = wait_for_result(sock);
    mark_pos(navy->en_board, pos, (res & HIT_FLAG) > 0);
    print_board(navy->en_win, navy->en_board, " Enemy's board ");
    if (res & WIN_FLAG) {
        print_status("I won", 5);
        return (1);
    } else
        return (0);
}

char en_turn(int sock, navy_t *navy)
{
    int pos;
    int hit;
    char lose;

    print_status("Enemy's turn", 12);
    pos = wait_for_position(sock);
    hit = get_pos(navy->my_board, pos);
    mark_pos(navy->my_board, pos, hit);
    print_board(navy->my_win, navy->my_board, " My board ");
    lose = check_lose(navy->my_board);
    send_result(sock, hit, lose);
    if (lose) {
        print_status("Enemy won", 9);
        return (1);
    } else
        return (0);
}

int play_turn(char host, int sock, navy_t *navy)
{
    if (host) {
        if (my_turn(sock, navy))
            return (0);
        if (en_turn(sock, navy))
            return (1);
    } else {
        if (en_turn(sock, navy))
            return (1);
        if (my_turn(sock, navy))
            return (0);
    }
    return (-1);
}
