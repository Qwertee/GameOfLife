#include "life.h"
#include <cstdlib>
#include <ncurses.h>
#include <time.h>
#include <algorithm>

#define STATUS_BAR_COLOR 1
#define BOARD_COLOR 2

static int width, height;

//colors for the board

void init(bool **board, int w, int h) {
    // srand() wants a uint so I'm casting it so my IDE stops complaining about type mismatches
    srand((unsigned int)time(NULL));
    width = w;
    height = h;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            //randomly draw a glider
            if (rand() % 50 < 1) {
                // check the bounds of the area to draw
                if (i + 2 < width && j + 2 < height) {
                    board[i][j] = 1;
                    board[i + 1][j] = 1;
                    board[i + 2][j] = 1;
                    board[i + 2][j + 1] = 1;
                    board[i + 1][j + 2] = 1;
                }
            } else if (rand() % 50 < 1) { // blinker
                if (i + 2 < width) {
                    board[i][j] = 1;
                    board[i + 1][j] = 1;
                    board[i + 2][j] = 1;
                }
            }
            else if (board[i][j] == 1) {
                continue;
            } else {
                board[i][j] = 0;
                board[i][j] = 0;
            }
        }
    }

    // initialize the colors for the
    init_pair(STATUS_BAR_COLOR, COLOR_BLACK, COLOR_GREEN);
    init_pair(BOARD_COLOR, COLOR_WHITE, COLOR_BLACK);
}

void updateBoard(bool **board) {
    // need a new board to fill to avoid messing with the current board
    bool nextBoard[width][height];

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            // need to count the neighbors of the cell
            int livingNeighbors = 0;
            for (int iOffset = -1; iOffset <= 1; iOffset++) {
                for (int jOffset = -1; jOffset <= 1; jOffset++) {
                    // we don't want to count the current cell as a neighbor of itself
                    if (iOffset == 0 && jOffset == 0) {
                        continue;
                    }

                    // make sure to stay in the bounds of the board
                    if ((i + iOffset >= 0 && i + iOffset < width) && (j + jOffset >= 0 && j + jOffset < height)) {
                        if (board[i + iOffset][j + jOffset]) {
                            livingNeighbors++;
                        }
                    }
                }
            } // end count

            if(board[i][j]) {
                if (livingNeighbors < 2 || livingNeighbors > 3) {
                    nextBoard[i][j] = 0;
                } else {
                    nextBoard[i][j] = 1;
                }
            } else {
                if (livingNeighbors == 3) {
                    nextBoard[i][j] = 1;
                } else {
                    nextBoard[i][j] = 0;
                }
            }
        }
    }

    // transfer the nextBoard to the old board
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            board[i][j] = nextBoard[i][j];
        }
    }
}

int countLiving(bool **board) {
    int numLiving = 0;
    for (int i = 0; i < width; ++i) {
        numLiving += std::count(board[i], board[i] + height, true);
    }
    return numLiving;
}

void draw(bool** board) {

    // first draw the board
    attron(COLOR_PAIR(BOARD_COLOR));
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            move(j, i);
            if (board[i][j]) {
                printw("0");
            } else {
                printw(" ");
            }
        }
    }
    attroff(COLOR_PAIR(BOARD_COLOR));

    // then draw the menu at the bottom of the screen
    // first the background bar
    attron(COLOR_PAIR(STATUS_BAR_COLOR));
    for (int i = 0; i < width; i++) {
        move(height, i);
        printw(" ");

    }

    // then write the text over it
    int numLiving = countLiving(board);
    static int max = 0, min = 9999;
    if(numLiving > max) {
        max = numLiving;
    }
    if (numLiving < min) {
        min = numLiving;
    }
    move(height, 0);
    printw("Keys: 'q'-quit, 'SPC'-pause, 's'-step");
    move(height, width - 12);
    printw("Living: %i", numLiving);
    move(height, width - 32);
    printw("%i/%i (min/max)", min, max);
    attroff(COLOR_PAIR(STATUS_BAR_COLOR));
}