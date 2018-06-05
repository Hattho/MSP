/**
 *  @file pre_game_autosolver_boards.c
 *  @brief C source code containing the body of the functions used to build and print the special chance board.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */

#include <stdlib.h>
#include <time.h>

#include "pre_game_autosolver_boards.h"

#define BOARDSIZE 18
#define NO_MINES 40
#define TRUE 1
#define FALSE 0

char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];
char solver_chance_board[BOARDSIZE][BOARDSIZE];

    /**
    *   void build_solver_chance_board()
    *   Function which builds the board that will hold
    *   the chances for every cell to be a bomb
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void build_solver_chance_board(){
    int iterator1;
    int iterator2;
    /// The line and column which is made of free spaces ' ' on the player board
    /// is replaced with -1 on the (int)solver_chance_board
     for(iterator1=0 ; iterator1 < BOARDSIZE ; iterator1++){
        for(iterator2=0; iterator2 < BOARDSIZE ; iterator2++){
            if(iterator1==0 || iterator1==BOARDSIZE-1){
                solver_chance_board[iterator1][iterator2] = -1;
            }
            else if(iterator2 == 0 || iterator2 == BOARDSIZE-1){
                solver_chance_board[iterator1][iterator2] = -1;
            }
            /// The rest of the elements are given the value 60, a value bigger than the sum that can be achieved
            /// by adding the adjacent player board cells' values
            else{
                solver_chance_board[iterator1][iterator2] = 60;
            }
        }
    }

}

    /**
    *   void print_solver_chance_board()
    *   Function which prints the solver chance board
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void print_solver_chance_board() {
    int iterator1;
    int iterator2;

    for( iterator1 = 0; iterator1 < BOARDSIZE  ; iterator1++){
        for( iterator2 = 0; iterator2 < BOARDSIZE  ; iterator2++){
            printf("%d ", solver_chance_board[iterator1][iterator2]);
        }
        printf("\n");
    }


}

