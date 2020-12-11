/*
** EPITECH PROJECT, 2020
** navy
** File description:
** main
*/

int main(int ac, char *av[])
{
    int enemy_pid;
    char host = ac == 2;
    char my_board[8][8];
    char en_board[8][8];
    int ret;

    if (ac < 2 || ac > 3 ||
    init_board(my_board, en_board, host ? av[1] : av[2]))
        return (84);
    if (ac == 3) {
        enemy_pid = my_getnbr(av[1]);
        init_signals(enemy_pid);
    } else if (ac == 2)
        enemy_pid = init_signals(-1);
    else
        return (84);
    while ((ret = play_turn(host, enemy_pid, my_board, en_board)) == -1);
    return (ret);
}