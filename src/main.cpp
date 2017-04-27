#include <sys/ioctl.h>
#include <zconf.h>
#include <ncurses.h>
#include "life.h"

void draw(bool** board);

int width;
int height;
int main() {
    initscr();

    // get the size of the terminal window
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    width = win.ws_row;
    height = win.ws_col;

    // generate array for the size of the terminal window
    bool **board = new bool *[width];
    for (int i = 0; i < width; i++) {
        board[i] = new bool[height];
    }
    init(board, width, height);
    draw(board);
    bool running = true;
//    while (running) {
//
//    }
    refresh();
    getch();
    endwin();
    return 0;
}

void draw(bool** board) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            move(i, j);
            if (board[i][j]) {
                printw("0");
            } else {
                printw(".");
            }
        }
    }
}