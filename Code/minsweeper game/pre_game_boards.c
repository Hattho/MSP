/**
 *  @file pre_game_boards.c
 *  @brief C source code containing the body of the functions that build and print the boards of the game.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#include "pre_game_boards.h"

#define BOARDSIZE 18
#define NO_MINES 15
#define TRUE 1
#define FALSE 0

char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];

    /**
    *   void build_mines_board()
    *   Function which builds the mines' board.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void build_mines_board(){

    int iterator1;
    int iterator2;
    int iterator3;
    int iterator4;
    int mine_row;
    int mine_col;
      for(iterator1=0 ; iterator1 < BOARDSIZE ; iterator1++){
        for(iterator2=0; iterator2 < BOARDSIZE ; iterator2++){
            /// The first row, first column, last row and last column are made of blank spaces
            if(iterator1==0 || iterator1==BOARDSIZE-1){
                mines_board[iterator1][iterator2] = ' ';
            }
            else if(iterator2==0 || iterator2== BOARDSIZE-1){
                mines_board[iterator1][iterator2] = ' ';
            }
            /// The other elements of the matrix are initialised as '0'
            else{
                mines_board[iterator1][iterator2] = '0';
            }
        }
    }



    srand(time(NULL));
    /// The mines are spawn randomly across the matrix, using rand function
    iterator1 = 1;
    while(iterator1 <= NO_MINES){
        mine_row = rand() % (BOARDSIZE -2) +1;
        mine_col = rand() % (BOARDSIZE -2) +1;
        /// When a mine is placed, the cells adjacent to it are incremented so we know how many mines are next to a cell.
        if(mines_board[mine_row][mine_col] != '*'){
            mines_board[mine_row][mine_col] = '*';
            increment(mine_row,mine_col+1);
            increment(mine_row,mine_col-1);
            increment(mine_row+1,mine_col);
            increment(mine_row-1,mine_col);
            increment(mine_row+1,mine_col+1);
            increment(mine_row+1,mine_col-1);
            increment(mine_row-1,mine_col-1);
            increment(mine_row-1,mine_col+1);
            iterator1++;
        }
     }


}

    /**
    *   void increment (int row, int column)
    *   We use this function to increment the cells next to the one where a mine is placed
    *   so we can find out how many mines are adjacent to a cell in the game.
    *   @param row The row on which the cell to be incremented is placed
    *   @param column The column on which the cell to be incremented is placed
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void increment (int row, int column){

    if( mines_board[row][column] != ' ' && mines_board[row][column] != '*' ){
        mines_board[row][column]++;
    }
    return;
}

    /**
    *   void print_mines_board()
    *   This function prints the mines board on the screen.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void print_mines_board(){

    int iterator1;
    int iterator2;
    /// We also print a line and a row of numbers which represent the coordinates of every position
    /// It is made in order to help the player know the exact coordinates of the cell he wants to flag or clear
    for(iterator1=0 ; iterator1< BOARDSIZE-1 ; iterator1++){
        /// Here we print the row of coordinates
        if(iterator1 < 10 && iterator1!=0 ){
            printf(" %d ", iterator1);
        }
        else if (iterator1 != 0){
            printf("%d ", iterator1);
        }
        else if(iterator1==0){
            printf("   ");
        }
    }

    printf("\n");

    for(iterator1 = 0; iterator1 < BOARDSIZE-1; iterator1++){
        for(iterator2 = 0; iterator2 < BOARDSIZE-1; iterator2++){
            printf(" %c ", mines_board[iterator1][iterator2]);
        }
        /// Here we print the column of coordinates
        if(iterator1 != 0){
            printf("  %d\n", iterator1);
        }
        else{
            printf("\n");
        }
    }
}
    /**
    *   void build_player_board()
    *   This function builds the board on which the player takes decisions and plays the game.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void build_player_board(){
    int iterator1;
    int iterator2;

    for(iterator1 = 0 ; iterator1 < BOARDSIZE ; iterator1++){
        for(iterator2 = 0; iterator2 < BOARDSIZE ; iterator2++){
            /// It places a row and column of blank spaces for artistic purposes
            if(iterator1 == 0 || iterator1 == BOARDSIZE-1){
                player_board[iterator1][iterator2] = ' ';
            }
            else if(iterator2 == 0 || iterator2 == BOARDSIZE-1){
                player_board[iterator1][iterator2] = ' ';
            }
            /// In rest, we place '-' as the hidden spaces on the player board
            else{
                player_board[iterator1][iterator2] = '-';
            }
        }
    }

}

    /**
    *   void print_player_board()
    *   This function prints the board on which the player takes decisions and plays the game.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void print_player_board(){

    int iterator1;
    int iterator2;
    /// We also print a line and a row of numbers which represent the coordinates of every position
    /// It is made in order to help the player know the exact coordinates of the cell he wants to flag or clear
    for(iterator1 = 0 ; iterator1 < BOARDSIZE-1 ; iterator1++){
        /// Here we print the row of coordinates
        if(iterator1 < 10 && iterator1!=0 ){
            printf(" %d ", iterator1);
        }
        else if (iterator1 != 0){
            printf("%d ", iterator1);
        }
        else if(iterator1==0){
            printf("   ");
        }
    }

    printf("\n");

    for(iterator1 = 0; iterator1 < BOARDSIZE-1; iterator1++){
        for(iterator2 = 0; iterator2 < BOARDSIZE-1; iterator2++){
            printf(" %c ", player_board[iterator1][iterator2]);
        }
        /// Here we print the column of coordinates
        if(iterator1 != 0){
            printf("  %d\n", iterator1);
        }
        else{
            printf("\n");
        }
    }
}
