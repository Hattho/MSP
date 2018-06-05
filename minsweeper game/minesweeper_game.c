/**
 *  @file minesweeper_game.c
 *  @brief C source code which contains the main function from where the game is generated and played.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "pre_game_boards.h"
#include "in_game_functions_player.h"

#define BOARDSIZE 18
#define NO_MINES 15
#define TRUE 1
#define FALSE 0



char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];

int main(){

    puts("\n");
    system("pause");
    start_game();

    return 0;
}




