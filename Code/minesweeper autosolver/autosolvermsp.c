/**
 *  @file autosolvermsp.c
 *  @brief C source code containing the main function that starts the autosolver.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "pre_game_boards.h"
#include "pre_game_autosolver_boards.h"
#include "in_game_functions_autosolver.h"

#define BOARDSIZE 18
#define NO_MINES 9
#define TRUE 1
#define FALSE 0

char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];
int solver_chance_board[BOARDSIZE][BOARDSIZE];

    /**
    *   int main()
    *   Function which starts the autosolver and calls the start_game function
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

int main(){


    puts("\n");
    system("pause");
    start_game();

    return 0;
}

