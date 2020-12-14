/*
** EPITECH PROJECT, 2020
** navy
** File description:
** bonus
*/

#ifndef BONUS_H_
#define BONUS_H_

#include <ncurses.h>

typedef struct {
    char my_board[8][8];
    char en_board[8][8];
    WINDOW *my_win;
    WINDOW *en_win;
    WINDOW *target_win;
} navy_t;

#define X_FACT 4
#define Y_FACT 2

#define ABS(value) (value < 0 ? -value : value)

char init_board(char my_board[8][8], char en_board[8][8], char *file);
void print_board(WINDOW *win, char board[8][8], char *title);
void end_game(char end);

char check_lose(char my_board[8][8]);
void ask_target(navy_t *navy, char buff[2]);
char my_turn(int sock, navy_t *navy);
char en_turn(int sock, navy_t *navy);
int play_turn(char host, int sock,
navy_t *navy);

void setup_board(char board[8][8]);
void set_boats(char board[8][8], char *boats[4]);
void mark_pos(char board[8][8], int pos, char hit);
char get_pos(char board[8][8], int pos);

void print_status(char *status, int len);

#endif /* !BONUS_H_ */