/*
** EPITECH PROJECT, 2020
** navy
** File description:
** board
*/

void setup_board(char board[8][8])
{
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++)
            board[x][y] = '.';
    }
}

static void place_boat(char board[8][8], int size, int pos, int end_pos)
{
    int x = pos / 10;
    int y = pos % 10;
    char dir;

    if (pos / 10 == end_pos / 10) {
        dir = pos % 10 < end_pos % 10 ? 1 : -1;
        for (int i = 0; i < size; i++)
            board[x][y + i * dir] = size + '0';
    } else {
        dir = pos / 10 < end_pos / 10 ? 1 : -1;
        for (int i = 0; i < size; i++)
            board[x + i * dir][y] = size + '0';
    }
}

void set_boats(char board[8][8], char *boats[4])
{
    int size;
    int start_pos;
    int end_pos;

    for (int i = 0; i < 4; i++) {
        size = boats[i][0] - '0';
        start_pos = (boats[i][2] - 'A') * 10 + (boats[i][3] - '1');
        end_pos = (boats[i][5] - 'A') * 10 + (boats[i][6] - '1');
        place_boat(board, size, start_pos, end_pos);
    }
}

void mark_pos(char board[8][8], int pos, char hit)
{
    int x = pos / 10;
    int y = pos % 10;

    board[x][y] = hit ? 'x' : 'o';
}

char get_pos(char board[8][8], int pos)
{
    int x = pos / 10;
    int y = pos % 10;
    char c = board[x][y];

    if (c >= '1' && c <= '4') {
        my_printf("%c%c: hit\n", 'A' + x, '1' + y);
        return (1);
    } else {
        my_printf("%c%c: miss\n", 'A' + x, '1' + y);
        return (0);
    }
}