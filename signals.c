/*
** EPITECH PROJECT, 2020
** navy
** File description:
** signals

*/

#include <stdlib.h>
#include <stddef.h>
#include <signal.h>
#include <unistd.h>
#include "network.h"
#include "my.h"

int VALUE = 0;

void send_message(int pid, int nb)
{
    unsigned int mask;

    kill(pid, SIGUSR2);
    for (char i = MSG_LENGTH; i >= 0; i--) {
        mask = 1 << i;
        if (!(nb & mask))
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(10000);
    }
}

static void receive_signal(int sig)
{
    if (sig == SIGUSR1)
        VALUE = VALUE << 1;
    else if (sig == SIGUSR2)
        VALUE = (VALUE << 1) + 1;
}

static void receive_pid(int sig, siginfo_t *info, void *context)
{
    if (sig == SIGUSR1) {
        VALUE = info->si_pid;
        my_putstr("\nenemy connected\n");
    } else
        my_putstr("successfully connected\n");
}

int get_value_send(int destroy)
{
    int ret = VALUE;

    if (destroy)
        VALUE = 0;
    return (ret);
}

int init_signals(int pid)
{
    struct sigaction sa;
    int ret = 0;

    sa.sa_sigaction = receive_pid;
    sa.sa_flags = SA_SIGINFO;
    my_printf("my_pid: %i\n", getpid());
    if (pid == -1) {
        my_putstr("waiting for enemy connection...\n");
        sigaction(SIGUSR1, &sa, NULL);
        pause();
        usleep(10000);
        kill(VALUE, SIGUSR2);
        ret = VALUE;
        VALUE = 0;
    } else {
        sigaction(SIGUSR2, &sa, NULL);
        kill(pid, SIGUSR1);
        pause();
    }
    signal(SIGUSR1, &receive_signal);
    signal(SIGUSR2, &receive_signal);
    return (ret);
}