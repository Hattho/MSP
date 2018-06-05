/**
 *  @file in_game_functions_autosolver.c
 *  @brief C source code containing the body of the functions used during the game itself.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */


#include <stdio.h>
#include <stdlib.h>
#include "in_game_functions_autosolver.h"


#define BOARDSIZE 18
#define NO_MINES 40
#define TRUE 1
#define FALSE 0

char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];
char solver_chance_board[BOARDSIZE][BOARDSIZE];

    /**
    *   void reveal_spaces (int row, int column)
    *   Function which reveals the space at the coordinates mentioned as parameters.
    *   @param row The row on which the cell to be revealed is placed
    *   @param column The column on which the cell to be revealed is placed
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void reveal_spaces (int row, int column){

        /// In case the function runs over a clear space outside of the game board, it stops
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
    /// When the cell is revealed, it's number on the solver chance board is reset,
    /// but not to 60 as when it is initialised, but to 59, to help with debugging
    /// to see if a cell was cleared or not.
    solver_chance_board[row][column] = 59;
    /// The loss trigger if the game hits a mine through the chance method of solving
    if(player_board[row][column]== '*'){
            loss();
            return;
        }

}

    /**
    *   void automatic_flagging()
    *   Function which runs the entire player board matrix looking for numbers and then
    *   calls another function which verifies if the number of mines shown by the cell
    *   match with the number of hidden spaces next to the cell and marks them as mine or reveals
    *   them depending on the case.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void automatic_flagging(){
    int iterator1;
    int iterator2;

    for( iterator1 = 1; iterator1 < BOARDSIZE -1; iterator1++){
        for( iterator2 = 1; iterator2 < BOARDSIZE -1; iterator2++){
            if( player_board[iterator1][iterator2] >= '1' && player_board[iterator1][iterator2] <= '9'){
                /// The cells which have a number of mines next to them are sent to a function
                /// which verifies if those mines can be pinpointed or not
                look_for_mines(iterator1, iterator2);
            }
        }
    }
}

    /**
    *   void look_for_mines (int row, int column)
    *   This function takes a cell with a number on it and looks around for hidden spaces
    *   and flagged spaces and decides whether the other hidden spaces around it are bombs or not
    *   This function is used to determine the hidden spaces that are 100% bombs or free spaces.
    *   @param row  The row where the cell which will be verified is placed
    *   @param column   The column where the cell which will be verified is placed
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void look_for_mines(int row, int column){
    /// A vector with the coordinates of the 8 cells around the one which is called
    int    coordinates_row[] = {0, 0, 1, -1, -1, -1, 1, 1};
    int coordinates_column[] = {1, -1, 0, 0, -1, 1, -1, 1};

    int hidden_spaces = 0;
    int mines = 0;

    int iterator1 = 0;
    int iterator2 = 0;
    /// We place the number on the player board cell inside an int variable for easier use
    int player_board_number = (int)(player_board[row][column] - '0');
    ///  The places around the cell are verified to see whether they are hidden spaces or flagged mines
    while(iterator1 <= 7){
        if(player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] == '-'){
            hidden_spaces++;
        }
        else if(player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] == 'M'){
            mines++;
        }
        iterator1++;
        iterator2++;
    }
    /// In case of no hidden spaces, the function stops
    if(hidden_spaces==0){
        return;
    }
    iterator1 = 0;
    iterator2 = 0;
    /// After we determine the number of adjacent flagged mines and hidden spaces
    /// we see if the hidden spaces are free or bombs
    /// We use this if statement to decide if the hidden spaces are free
    if( (mines == player_board_number) && (hidden_spaces != 0) ){
        while(iterator1 <= 7){
            if(player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] == '-'){
                reveal_spaces(row+coordinates_row[iterator1], column+coordinates_column[iterator2]);
            }
            iterator1++;
            iterator2++;
        }
    }
    /// We use this if statement to decide if the hidden spaces are bombs
    else if (hidden_spaces == player_board_number - mines) {
        while(iterator1 <= 7){
            if(player_board[row+coordinates_row[iterator1]][column + coordinates_column[iterator2]] == '-'){
                player_board[row+coordinates_row[iterator1]][column + coordinates_column[iterator2]] = 'M';
            }
            iterator1++;
            iterator2++;
        }
    }
}

    /**
    *   void automatic_chance_placer()
    *   Function which places a chance for every cell on the board to be a bomb.
    *   This function is called after we determine there are no more "sure" bombs and free spaces.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void automatic_chance_placer(){
    int iterator1;
    int iterator2;
    /// Every hidden space receives a chance to be a bomb which is calculated in the place_chance function
    for( iterator1 = 1; iterator1 < BOARDSIZE -1; iterator1++){
        for( iterator2 = 1; iterator2 < BOARDSIZE -1; iterator2++){
            if(player_board[iterator1][iterator2] == '-'){
                    place_chance(iterator1, iterator2);
            }
        }
    }

}

    /**
    *   void place_chance(int row, int column)
    *   Function which gives every hidden space a chance to be a bomb by adding the values
    *   of the cells with numbers on the player board that are next to the hidden space.
    *   @param  row The row where the cell which will be given its chance to be a bomb is placed
    *   @param  column The column where the cell which will be given its chance to be a bomb is placed
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */

void place_chance(int row, int column){
    /// A vector with the coordinates of the 8 cells around the one which is called
    int    coordinates_row[] = {0, 0, 1, -1, -1, -1, 1, 1};
    int coordinates_column[] = {1, -1, 0, 0, -1, 1, -1, 1};

    int iterator1 = 0;
    int iterator2 = 0;
    int confirm = 0;
    /// We look to see if there are any adjacent cells with the numbers on the player board
    while(iterator1 <= 7){
        if( player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] >= '1'
           && player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] <= '9'){
               confirm = 1;
               break;

        }
        iterator1++;
        iterator2++;
    }
    /// If there are cells with numbers next to our cell, we reset its value on the solver chance board
    if( confirm ){
        solver_chance_board[row][column] = 0;
    }
    /// We add the values of the cells next to ours which contain numbers to decide its likelihood of being a bomb.
    while(iterator1 <= 7){
        if( player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] >= '1'
           && player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] <= '9'){
            solver_chance_board[row][column] += (int)(player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] - '0' );
        }
        iterator1++;
        iterator2++;
    }


}

    /**
    *   void automatic_decision_taker()
    *   Function which runs the entire board of cells and looks for
    *   the hidden space with the lowest chance of being a bomb.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void automatic_decision_taker(){
    int iterator1;
    int iterator2;
    /// We need to find the coordinates of the lowest chance cell and
    /// also reset the value of the minimum chance whenever we find another minimum
    int iterator1_minimum_chance = 0;
    int iterator2_minimum_chance = 0;
    int minimum_chance_recorded = 55;
    /// We run the entire board and save the coordinates of the new minimum as well as its value
    for( iterator1 = 1; iterator1 < BOARDSIZE -1; iterator1++){
        for( iterator2 = 1; iterator2 < BOARDSIZE -1; iterator2++){
            if(player_board[iterator1][iterator2] == '-' && solver_chance_board[iterator1][iterator2] < minimum_chance_recorded){
                 iterator1_minimum_chance = iterator1;
                 iterator2_minimum_chance = iterator2;
                 minimum_chance_recorded = solver_chance_board[iterator1][iterator2];
            }
        }
    }
    /// We reveal the space with the lowest chance, praying to God that it is not a bomb.
    reveal_spaces(iterator1_minimum_chance, iterator2_minimum_chance);

}

    /**
    *   void loss()
    *   Function which is called when the computer steps on a mine and loses the game.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void loss(){
    char answer;

    print_mines_board();

    printf("\n");
    /// The function let's you decide whether you want to run the program or not, we suggest you do
    printf("\nYou lost. Clearly your mistake, not the computer's.");
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
    *   Function which is called when the computer clears all the hidden spaces and wins the game.
    *   @author Efrem Stefan and Hagiu Teodora
    *   @date 6/05/2018
    */


void win(){
    char answer;

    printf("\n You got to live until the end. Good job! :)");
    /// The function let's you decide whether you want to run the program or not, we suggest you do
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
    for(iterator1 = 1; iterator1 < BOARDSIZE-1 ; iterator1++){
        for(iterator2 = 1; iterator2 < BOARDSIZE-1 ; iterator2++) {
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


    /// Builds the mines, player and solver chance boards
    build_mines_board();
    build_player_board();
    build_solver_chance_board();
    print_player_board();

    printf("Welcome to our minesweeper autosolver!\n");
    /// The program let's the player make the first move
    int first_move = 1;

    for(;;){

        if( first_move ){
            do {

                printf("You make the first move, we'll do the rest :) \n");
                printf("Row: ");
                scanf("%d", &row);
                printf("Column: ");
                scanf("%d", &column);
                printf("\n");
            } while(row < 1 || row > BOARDSIZE - 2 || column < 1 || column > BOARDSIZE - 2);
        }

        /// Reveals the space chosen by the player at the first move of the game
        if( first_move ){
            reveal_spaces( row, column);
        }
        first_move = 0;
        /// Let's the player see the progress of the computer after every step.
        printf("Press 1 to run another step of the auto solver and see the progress made! \n");
        int step;
        scanf("%d", &step);

        if(step == 1){
            /// First the game verifies if the are any sure mines or free spaces, then the chance method is used
            automatic_flagging();
            automatic_chance_placer();
            automatic_decision_taker();
            /// The output screen is cleared and the progress is updated, the step is done
            system("cls");

            print_player_board();

            printf("\n");
        }

        /// The program checks to see if the game has been won
        if(check_win() == TRUE){
            win();
        }

    }

}
