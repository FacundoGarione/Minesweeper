#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"

bool game_over = false;
bool game_won = false;
static int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

struct cell_s{
    int adjacentsAmount;
    bool hasMine;
    bool selected;
    bool flagged;
};

struct board_s{
    unsigned int size;
    cell **cells;
};

cell new_cell(void){

    cell result = malloc(sizeof(struct cell_s));
    //cond
    result->adjacentsAmount = 0;
    result->hasMine = false;
    result->selected = false;
    result->flagged = false;

    return result;
}

cell destroy_cell(cell c){
    if(c != NULL){
        free(c);
        c = NULL;
    }
    return c;
}

void printCell(cell c){
    if(c != NULL){
        if(c->selected){
            if(c->hasMine){
                printf(LIGHT_RED "X" RESET);
            }
            else{
                const char *colors[] = {BLACK, LIGHT_BLUE, GREEN, LIGHT_RED, DARK_BLUE, 
                DARK_RED, CYAN, PINK, PURPLE};

                int adjacents = c->adjacentsAmount;
                if(adjacents >= 0 && adjacents <= 8){
                    printf("%s%d" RESET, colors[adjacents], adjacents);
                }
            }
        }
        else if(c->flagged){
            printf(ORANGE "▲" RESET);
        }
        else{
            printf("#");
        }
    }
}

void select_cell(board b, unsigned int x, unsigned int y){
    if(b == NULL){
        printf("Board is NULL\n");
        return;
    }
    if(x >= b->size || y >= b->size){
        printf("Invalid coords\n");
        return;
    }

    cell c = b->cells[x][y];
    if(c != NULL){
        c->selected = true;
        if(c->hasMine){
            printf(BOLD_RED "Game Over! You hit a mine at (%u, %u)\n" RESET, x, y);
            game_over = true;
        }
        else{
            reveal_cell(b, x, y);
        }
    }
    else{
        printf("Invalid cell\n");
    }
}

void flag_cell(board b, unsigned int x, unsigned int y){
    if(b == NULL){
        printf("Board is NULL\n");
        return;
    }
    if(x >= b->size || y >= b->size){
        printf("Invalid coords\n");
        return;
    }

    cell c = b->cells[x][y];
    if(c != NULL){
        c->flagged = !c->flagged;;
    }
    else{
        printf("Invalid cell\n");
    }
}

void reveal_cell(board b, unsigned int x, unsigned int y) {
    if(x >= b->size || y >= b->size){
        printf("Coords (%u, %u) out of bounds\n", x, y);
        return; 
    }

    cell c = b->cells[x][y];
    if(c == NULL){
        printf("Cell (%u, %u) is NULL\n", x, y);
        return;
    }
    if(c->hasMine){
        return; 
    }

    c->selected = true;

    if(c->adjacentsAmount == 0){
        for (int i = 0; i < 8; i++){
            int nx = x + directions[i][0];
            int ny = y + directions[i][1];
            if (nx >= 0 && nx < (int)b->size && ny >= 0 && ny < (int)b->size) {
                if(!b->cells[nx][ny]->selected){
                    reveal_cell(b, nx, ny);
                }
            }
        }
    }
}

board buildBoard(unsigned int size){
    board result = malloc(sizeof(struct board_s));
    result->size = size;

    result->cells = malloc(size * sizeof(cell*));
    //cond
    for(unsigned int i=0; i<size; i++){
        result->cells[i] = malloc(size * sizeof(cell));
        //cond
        for(unsigned int j=0; j<size; j++){
            result->cells[i][j] = new_cell();
        }
    }

    return result;
}

void placeBombs(board b, int *safeCells, unsigned int sc_x, unsigned int sc_y){
    if(b != NULL){
        unsigned int size = b->size;
        unsigned int minesNum = (size * size) * 0.30;
        unsigned int radius = (size <= 5) ? 1 : (size < 10) ? 2 : 3;
        
        srand((unsigned int)time(NULL));
        unsigned int minesPlaced = 0;
        while(minesPlaced<minesNum){
            unsigned int x = rand() % size;
            unsigned int y = rand() % size;
            
            if(!b->cells[x][y]->hasMine && !isSafeZone(x, y, sc_x, sc_y, radius)){
                b->cells[x][y]->hasMine = true;
                minesPlaced++;
            }
        }

        *safeCells = (size*size) - minesPlaced;

        for(unsigned int i = 0; i < size; i++){
            for(unsigned int j = 0; j < size; j++){
                b->cells[i][j]->adjacentsAmount = countAdjacentMines(b, i, j);
            }
        }
    }
}

bool isSafeZone(unsigned int x, unsigned int y, unsigned int sc_x, unsigned int sc_y, unsigned int radius){
    //Euclidean distance formula
    unsigned int dx = (x >= sc_x) ? x - sc_x : sc_x - x;
    unsigned int dy = (y >= sc_y) ? y - sc_y : sc_y - y;
    return (dx * dx + dy * dy) <= (radius * radius);
}

board destroy_board(board b){
    if(b != NULL){
        for(unsigned int i = 0; i<b->size; i++){
            if (b->cells[i] != NULL){
                for (unsigned int j = 0; j<b->size; j++){
                    b->cells[i][j] = destroy_cell(b->cells[i][j]); 
                }
                free(b->cells[i]);
            }
        }
        free(b->cells);
        free(b); 
        b = NULL;
    }
    return b;
}

void delay(unsigned int ms){
    clock_t start_time = clock();
    unsigned int delay_time = ms * (CLOCKS_PER_SEC / 1000);
    while(clock() < start_time + delay_time){
        //delay loop
    }
}

void printBoard(board b, bool first_print){
    printf(" ");
    for(unsigned int i = 0; i < b->size; i++){
        if(i<10){
            printf(BOLD_DARK_GREEN "  %d" RESET, i);
        }
        else{
            printf(BOLD_DARK_GREEN " %d" RESET, i);
        }
    }
    printf("\n");

    for(unsigned int i = 0; i < b->size; i++){
        if(i<10){
            printf(BOLD_DARK_GREEN "%d  " RESET, i);
        }
        else{
            printf(BOLD_DARK_GREEN "%d " RESET, i); 
        }
        for(unsigned int j = 0; j < b->size; j++){
            if(game_over){
                if(b->cells[i][j]->hasMine){
                    if(game_won){
                        printf(GRAY "X" RESET);
                    }
                    else{
                        printf(VERY_LIGHT_RED "X" RESET);
                    }
                }
                else{
                    printCell(b->cells[i][j]);
                }
            }
            else{
                printCell(b->cells[i][j]);
            }
            printf("  ");
        }
        printf("\n");
        if(first_print){
            delay(250);
        }
    }
}

int countAdjacentMines(board b, unsigned int x, unsigned int y) {
    int count = 0;

    for(int i = 0; i < 8; i++){
        int nx = x + directions[i][0];
        int ny = y + directions[i][1];

        if(nx >= 0 && nx < (int)b->size && ny >= 0 && ny < (int)b->size){
            if(b->cells[nx][ny]->hasMine){
                count++;
            }
        }
    }

    return count;
}

void check_win(board b, int safeCells){
    int revealed_cells=0;

    for(unsigned int i=0; i<b->size; i++){
        for(unsigned int j=0; j<b->size; j++){
            if(b->cells[i][j]->selected && !b->cells[i][j]->hasMine){
                revealed_cells++;
            }
        }
    }

    if(revealed_cells == safeCells){
        printf(GREEN "You won!\n" RESET);
        game_over = true;
        game_won = true;
        printBoard(b, false);
    }
}

