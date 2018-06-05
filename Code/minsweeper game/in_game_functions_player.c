/**
 *  @file in_game_functions_player.c
 *  @brief C source code containing the functions used during the game itself.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "in_game_functions_player.h"
#include "pre_game_boards.h"

#define BOARDSIZE 18
#define NO_MINES 15
#define TRUE 1
#define FALSE 0

char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];

    /**
    *   void reveal_spaces (int row, int column)
    *   Function which reveals the space at the coordinates mentioned as parameters.
    *   @param row The row on which the cell to be revealed is placed
    *   @param column The column on which the cell to be revealed is placed
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void reveal_spaces (int row, int column){
        /// In case the function runs over a clear space outrside of the game board, it stops
        if(mines_board[row][column] == ' '){
            return;
        }

        player_board[row][column] = mines_board[row][column];
        /// In case the function runs over a cell which has 0 mines nearby,
        /// it clears all surrounding cells with the same property.
        if(mines_board[row][column] == '0'){
            mines_board[row][column] = '~';
            player_board[row][column] = '~';
            reveal_spaces(row+1,column);
            reveal_spaces(row-1,column);
            reveal_spaces(row,column+1);
            reveal_spaces(row,column-1);
            reveal_spaces(row+1,column+1);
            reveal_spaces(row+1,column-1);
            reveal_spaces(row-1,column+1);
            reveal_spaces(row-1,column-1);

        }

}

    /**
    *   void loss()
    *   Function which is called when the player steps on a mine and loses the game.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void loss(){
    char answer;

    printf("\nYou're dead. Sorry :)");
    /// The function let's you decide whether you want to play again or not, we suggest you do
    printf("\nWanna try to live this time? (y/n)--> ");
    scanf(" %c", &answer);
    /// Restarts the game in case of a positive answer
    if(answer == 'y'){
        system("cls");
        start_game();
    }
    else
        exit(0);
}

    /**
    *   void win()
    *   Function which is called when the player clears all the hidden spaces and wins the game.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void win(){
    char answer;

    printf("\n You got to live until the end. Good job! :)");
    /// The function let's you decide whether you want to play again or not, we suggest you do
    printf("\nWanna try to die this time? (y/n)--> ");
    scanf(" %c", &answer);
    /// Restarts the game in case of a positive answer
    if(answer == 'y'){
        system("cls");
        start_game();
    }
    else
        exit(0);

}

    /**
    *   void check_win()
    *   Function which is called to verify if the player has won the game with the last move he made.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

int check_win(){
    int iterator1;
    int iterator2;
    /// Verifies if there are any more unmarked bombs and hidden spaces
    for(iterator1 = 1; iterator1 < BOARDSIZE - 1; iterator1++){
        for(iterator2 = 1; iterator2 < BOARDSIZE - 1; iterator2++) {
            if(player_board[iterator1][iterator2] == '-' && mines_board[iterator1][iterator2] != '*'){
                return FALSE;
            }
        }
    }

    return TRUE;
}

    /**
    *   void start_game()
    *   Function which starts the game.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void start_game(){


 int row, column;
    /// The mines and player boards are made
    build_mines_board();
    build_player_board();
    print_player_board();
    /// The legend of the game is shown to familiarize the player
    printf("Welcome to our minesweeper. Hope you will have a great stay :)\n");
    printf("Legend:\n M -- Flagged mine \n ~ -- Clear space(without any bombs around it) \n - -- Spaces not yet cleared \n 1-8 -- Number of mines around the tile\n");

    int decision;
    for(;;){


        do {
            /// Player decides whether to clear a cell or flag it as a mine
            printf("Do you want to clear a space or flag a bomb?: 0--clear / 1-- flag a mine\n");

            printf("Decision: ");
            scanf("%d", &decision);

            printf("Row: ");
            scanf("%d", &row);

            printf("Column: ");
            scanf("%d", &column);

            printf("\n");
        } while(row < 1 || row > BOARDSIZE - 2 || column < 1 || column > BOARDSIZE -2);


        if( !decision ){
            /// If the cell cleared is a mine, the game is lost
            if(mines_board[row][column] == '*'){
                printf("We told you that you'll die :)\n");
                print_mines_board();
                loss();
            }
            else{
                ///The cell chosen is cleared
                reveal_spaces(row, column);
            }
        }
        else {
            /// The cell chosen is flagged as a mine
            if ( decision ) {
                player_board[row][column] = 'M';
            }
        }
        /// The output screen is cleared and the progress is updated, waiting for a new move from the player
        system("cls");
        print_player_board();
        /// The program checks to see if the player has won the game
        if(check_win() == TRUE){
            win();
        }

    }
}
