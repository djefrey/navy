/*
** EPITECH PROJECT, 2020
** navy
** File description:
** network
*/

#include <signal.h>
#include "network.h"
#include "my.h"

static int wait_for_message(void)
{
    while (!(get_value_send(0) & END_MESSAGE))
        pause();
    return (get_value_send(1) - END_MESSAGE);
}

int send_position(int pid, char pos[2])
{
    int x = pos[0] - 'A';
    int y = pos[1] - '1';
    int intpos = x * 10 + y;

    if (x < 0 || x > 7 || y < 0 || y > 7)
        return (1);
    send_message(pid, intpos + POS_FLAG);
    return (0);
}

int wait_for_position(void)
{
    int value;

    my_putstr("waiting for enemy's attack...\n");
    value = wait_for_message();
    return (value & POS_MASK);
}

int send_result(int pid, char hit, char enemy_win)
{
    int value = hit * HIT_FLAG + enemy_win * WIN_FLAG;

    send_message(pid, value);
}

int wait_for_result(void)
{
    int value = wait_for_message();

    return (value & RESULT_MASK);
}