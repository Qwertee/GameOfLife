#include "life.h"
#include <cstdlib>
#include <ncurses.h>
#include <time.h>

static int width, height;

//colors for the board

void init(bool **board, int w, int h) {
    srand(time(NULL));
    width = w;
    height = h;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            //randomly draw a glider
            if (rand() % 75 < 1) {
                // check the bounds of the area to draw
                if (i + 2 < width && j + 2 < height) {
                    board[i][j] = 1;
                    board[i + 1][j] = 1;
                    board[i + 2][j] = 1;
                    board[i + 2][j + 1] = 1;
                    board[i + 1][j + 2] = 1;
                }
            } else if (rand() % 75 < 1) { // blinker
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
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    init_pair(2, COLOR_RED, COLOR_BLUE);
}

void updateBoard(bool **board) {
    // need a new board to fill to avoid messing with the current board
    // TODO: Make this more efficient
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

void draw(bool** board) {

    // first draw the board
    attron(COLOR_PAIR(2));
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
    attroff(COLOR_PAIR(2));

    // then draw the menu at the bottom of the screen
    // first the background bar
    attron(COLOR_PAIR(1));
    for (int i = 0; i < width; i++) {
        move(height, i);
        printw(" ");

    }

    // then write the text over it
    move(height, 0);
    printw("Keys: 'q'-quit");
    attroff(COLOR_PAIR(1));
}