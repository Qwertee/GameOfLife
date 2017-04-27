#include <sys/ioctl.h>
#include <zconf.h>
#include <ncurses.h>
#include <vector>
#include <iostream>
#include <thread>
#include "life.h"


static int width;
static int height;
int main() {
    initscr();
    curs_set(0);
    noecho();

    // get the size of the terminal window
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    width = win.ws_col;
    height = win.ws_row;

    // generate array for the size of the terminal window
    bool **board = new bool *[width];
    for (int i = 0; i < width; i++) {
        board[i] = new bool[height];
    }
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            board[i][j] = 0;
        }
    }

    init(board, width, height);
    draw(board);
    refresh();
    bool running = true;

    // main loop of the program
    // TODO: Add a way to quit the game without having to kill it
    while (running) {
        updateBoard(board);
        draw(board);
        refresh();
        // sleep for a bit to pace the execution of the program
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    endwin();
    return 0;
}

