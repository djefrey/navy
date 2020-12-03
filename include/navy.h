/*
** EPITECH PROJECT, 2020
** navy
** File description:
** navy
*/

#ifndef NAVY_H_
#define NAVY_H_

void print_board(char board[8][8]);
char end_game(char end);

char check_lose(char my_board[8][8]);
void ask_target(char buff[2]);
char my_turn(int enemy_pid, char en_board[8][8]);
char en_turn(int enemy_pid, char my_board[8][8]);
int play_turn(char host, int enemy_pid,
char my_board[8][8], char en_board[8][8]);

void setup_board(char board[8][8]);
void set_boats(char board[8][8], char *boats[4]);
void mark_pos(char board[8][8], int pos, char hit);
char get_pos(char board[8][8], int pos);

#endif /* !NAVY_H_ */