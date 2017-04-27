#ifndef GAMEOFLIFE_LIFE_H
#define GAMEOFLIFE_LIFE_H

/**
 * Initializes the board with a default game state
 * @param board the board to be initialized
 */
void init(bool** board, int width, int height);

/**
 * updates the board per the rules of the Game of Life
 * @param board the board to be updated
 */
void updateBoard(bool **board);

/**
 * print the board to the screen
 * assumes ncurses is already set up and started
 * @param board board to print
 */
void draw(bool **board);

#endif //GAMEOFLIFE_LIFE_H
