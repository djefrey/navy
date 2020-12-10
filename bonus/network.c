/*
** EPITECH PROJECT, 2020
** navy
** File description:
** network
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include "network.h"
#include "my.h"

int send_position(int sock, char pos[2])
{
    int x = pos[0] - 'A';
    int y = pos[1] - '1';
    int value = x * 10 + y + POS_FLAG;

    if (x < 0 || x > 7 || y < 0 || y > 7)
        return (1);
    if (send(sock, &value, sizeof(int), 0) < 0) {
        perror("Error while sending packet");
        exit(84);
    }
    return (0);
}

int wait_for_position(int sock)
{
    int value;
    int n;

    my_putstr("waiting for enemy's attack...\n");
    if ((n = recv(sock, &value, sizeof(int), 0)) < 0) {
        perror("Error while receiving packet");
        exit(84);
    }
    return (value & POS_MASK);
}

int send_result(int sock, char hit, char enemy_win)
{
    int value = hit * HIT_FLAG + enemy_win * WIN_FLAG;

    if (send(sock, &value, sizeof(int), 0) < 0) {
        perror("Error while sending packet");
        exit(84);
    }
    return (0);
}

int wait_for_result(int sock)
{
    int value;
    int n;

    if ((n = recv(sock, &value, sizeof(int), 0)) < 0) {
        perror("Error while receiving packet");
        exit(84);
    }
    return (value & RESULT_MASK);
}