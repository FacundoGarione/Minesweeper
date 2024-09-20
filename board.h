#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>

extern bool game_over;//global bool
extern bool game_won;

typedef struct cell_s * cell;

typedef struct board_s * board;

cell new_cell(void);

cell destroy_cell(cell c);

void printCell(cell c);

void select_cell(board b, unsigned int x, unsigned int y);

void flag_cell(board b, unsigned int x, unsigned int y);

void reveal_cell(board b, unsigned int x, unsigned int y);

board buildBoard(unsigned int size);

void placeBombs(board b, int *safeCells, unsigned int sc_x, unsigned int sc_y);

bool isSafeZone(unsigned int x, unsigned int y, unsigned int sc_x, unsigned int sc_y, unsigned int radius);

board destroy_board(board b);

void delay(unsigned int ms);

void printBoard(board b, bool first_print);

int countAdjacentMines(board b, unsigned int x, unsigned int y);

void check_win(board b, int safeCells);

//colors
#define RESET "\033[0m"
#define BLACK "\033[0;30m"
#define LIGHT_BLUE "\033[0;94m"
#define DARK_BLUE "\033[0;34m"
#define CYAN "\033[0;96m"
#define GREEN "\033[0;32m"
#define DARK_GREEN "\033[38;5;22m"
#define BOLD_DARK_GREEN "\033[1;38;5;22m"
#define LIGHT_RED "\033[0;91m"
#define DARK_RED "\033[0;31m"
#define BOLD_RED "\033[1;31m"
#define ORANGE "\033[38;5;208m"
#define PINK "\033[0;35m"
#define PURPLE "\033[0;35m"
#define GRAY "\033[38;5;238m"
#define VERY_LIGHT_RED "\033[38;5;196m"

#endif