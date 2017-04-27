#include "life.h"
#include <cstdlib>

void init(bool **board, int width, int height) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            //randomly draw a glider
            if (rand() % 800 < 1) {
                // check the bounds of the area to draw
                if (i + 2 < width && j + 2 < height) {
                    board[i][j] = 1;
                    board[i + 1][j] = 1;
                    board[i + 2][j] = 1;
                    board[i + 2][j + 1] = 1;
                    board[i + 1][j + 2] = 1;
                }
            } else if (rand() % 800 < 1) { // blinker
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
}