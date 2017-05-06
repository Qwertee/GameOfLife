#include <sys/ioctl.h>
#include <zconf.h>
#include <ncurses.h>
#include <vector>
#include <thread>
#include "life.h"

static int width;
static int height;
int main() {
    initscr();              // start curses mode
    curs_set(0);            // hide the cursor
    raw();                  // get each char individually
    noecho();               // dont put the inputted character to the screen
    nodelay(stdscr, true);  // for continuous input
    start_color();          // for color

    // get the size of the terminal window
    struct winsize win;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &win);
    width = win.ws_col;
    height = win.ws_row - 1;

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
    int ch;
    bool paused = false;
    while (running) {
        if(!paused) {
            updateBoard(board);
            draw(board);
            refresh();
        }

        // check if the user has pressed q to quit
        ch = getch();
        if (ch != ERR) {
            if (ch == 'q') {
                running = false;
            }
            else if (ch == ' ') {
                paused = !paused;
            }
        }
        // sleep for a bit to pace the execution of the program
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    endwin();
    return 0;
}

