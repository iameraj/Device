#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define VERSION "0.0.1"

void panic(const char* msg)
{
        perror(msg);
        exit(1);
}

int get_window_height()
{

        struct winsize temp;
        int res = ioctl(STDOUT_FILENO, TIOCGWINSZ, &temp);
        if (res == -1) panic("Error while getting window size");
        if (temp.ws_col == 0) panic("Invalid Col size");

        return temp.ws_row;
};
int get_window_width()
{

        struct winsize temp;
        int res = ioctl(STDOUT_FILENO, TIOCGWINSZ, &temp);
        if (res == -1) panic("Error while getting window size");
        if (temp.ws_col == 0) panic("Invalid Col size");

        return temp.ws_col;
};

void put_pixel(int x, int y, const char ch)
{
        char cmd[32];
        write(STDOUT_FILENO, "\033[s", 3);
        int len = snprintf(cmd, sizeof(cmd), "\x1b[%d;%dH", x, y);
        write(STDOUT_FILENO, cmd, len);
        write(STDOUT_FILENO, &ch, 1);
        write(STDOUT_FILENO, "\033[u", 3);
};

void clrscr()
{
        write(STDOUT_FILENO, "\x1b[H", 3);
        write(STDOUT_FILENO, "\x1b[J", 3);
        write(STDOUT_FILENO, "\x1b[H", 3);
}

void getch()
{
        char ch;
        while (read(STDIN_FILENO, &ch, 1) == 0);
}
