/*
** EPITECH PROJECT, 2020
** navy
** File description:
** network
*/

#ifndef NETWORK_H_
#define NETWORK_H_

#define MSG_LENGTH 15
#define END_MESSAGE 65536

#define POS_FLAG 128
#define POS_MASK 127

#define HIT_FLAG 256
#define WIN_FLAG 512
#define RESULT_MASK 768

int send_position(int pid, char pos[2]);
int wait_for_position(void);
int send_result(int pid, char hit, char enemy_win);
int wait_for_result(void);

void send_message(int pid, int nb);

int init_signals(int pid);
int get_value_send(int destroy);

#endif /* !NETWORK_H_ */