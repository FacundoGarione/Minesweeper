#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "board.h"

int main(void){
    unsigned int size, x ,y, first_x, first_y;
    char c;
    bool first_selected = false;

    srand((unsigned int)time(NULL));

    printf("Select board size: ");
    if(scanf("%u", &size) != 1 || size == 0){
        printf("Size must be positive\n");
        return EXIT_FAILURE;
    }

    int safeCells=0;
    board my_board = buildBoard(size);
    if(my_board == NULL){
        printf("Board creation failure\n");
        return EXIT_FAILURE;
    }

    printBoard(my_board, true);

    while(!first_selected){
        printf("Write s (y x) to select the x y cell: ");
        int res_first = scanf(" %c", &c);
        if(res_first == 1 && c == 's'){
            if(scanf("%u %u", &first_x, &first_y) != 2){
                printf("Invalid input\n");
                // clean buffer
                while(getchar() != '\n');
            }
            else if(size <= first_x || size <= first_y){
                printf("Invalid coords\n");
                // clean buffer
                while(getchar() != '\n');
            }
            else{
                first_selected = true;
            }
        }
        else{
            printf("Select a cell\n");
            // clean buffer
            while(getchar() != '\n');
        }
    }

    placeBombs(my_board, &safeCells, first_x, first_y);
    select_cell(my_board, first_x, first_y);
    check_win(my_board, safeCells); // in case size=1
    printBoard(my_board, false);

    while(!game_over){
        printf("Write s (y x) to select the x y cell or f (y x) to flag/unflag, q to quit: ");

        // read command
        int result = scanf(" %c", &c);

        if(result == 1 && c == 'q'){
            break;
        }
        else if(result == 1 && (c == 's' || c == 'f')){
            // read coords
            if(scanf("%u %u", &x, &y) == 2){
                if(c == 'f'){
                    flag_cell(my_board, x, y);
                }else if (c == 's'){
                    select_cell(my_board, x, y);
                }
            }
            else{
                printf("Invalid input\n");
                // clean buffer
                while(getchar() != '\n');
            }
        }
        else{
            printf("Invalid command\n");
            // clean buffer
            while(getchar() != '\n');
        }
        printBoard(my_board, false);
        check_win(my_board, safeCells);
    }
    destroy_board(my_board);
    my_board = NULL;

    return EXIT_SUCCESS;
}