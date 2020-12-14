/*
** EPITECH PROJECT, 2020
** navy
** File description:
** windows
*/

#include <ncurses.h>
#include "bonus.h"

void print_status(char *status, int len)
{
    for (int i = 0; i < COLS; i++)
        mvaddch(LINES / 8 * 7, i, ' ');
    mvprintw(LINES / 8 * 7, COLS / 2 - len / 2, status);
}

static void init_my_board_win(navy_t *navy)
{
    int y = LINES / 8;
    int x = COLS / 2 - 51;
    int height = 21;
    int width = 42;

    navy->my_win = subwin(stdscr, height, width, y, x);
    print_board(navy->my_win, navy->my_board, " My board ");
}

static void init_en_board_win(navy_t *navy)
{
    int y = LINES / 8;
    int x = COLS / 2 + 11;
    int height = 21;
    int width = 42;

    navy->en_win = subwin(stdscr, height, width, y, x);
    print_board(navy->en_win, navy->en_board, "Enemy's board");
}

static void init_target_win(navy_t *navy)
{
    int y = LINES / 8 * 6;
    int x = COLS / 2 - 3;
    int height = 3;
    int width = 6;

    navy->target_win = subwin(stdscr, height, width, y, x);
    box(navy->target_win, ACS_VLINE, ACS_HLINE);
    wrefresh(navy->target_win);
}

void init_windows(navy_t *navy)
{
    initscr();
    attron(A_BOLD);
    mvprintw(1, COLS / 2 - 2, "Navy");
    attroff(A_BOLD);
    init_my_board_win(navy);
    init_en_board_win(navy);
    init_target_win(navy);
    refresh();
    noecho();
    curs_set(0);
}