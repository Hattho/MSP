#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define BOARDSIZE 12
#define NO_MINES 9
#define TRUE 1
#define FALSE 0

char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];
int solver_chance_board[BOARDSIZE][BOARDSIZE];


void build_mines_board(){

    int iterator1;
    int iterator2;
    int iterator3;
    int iterator4;
    int mine_row;
    int mine_col;

     for(iterator1=0 ; iterator1 < BOARDSIZE ; iterator1++){
        for(iterator2=0; iterator2 < BOARDSIZE ; iterator2++){
            if(iterator1==0 || iterator1==BOARDSIZE-1){
                mines_board[iterator1][iterator2]=' ';
            }
            else if(iterator2==0 || iterator2== BOARDSIZE-1){
                mines_board[iterator1][iterator2]=' ';
            }

            else{
                mines_board[iterator1][iterator2]='0';
            }
        }
    }

    srand(time(NULL));

     iterator1=1;
     while(iterator1<=NO_MINES){
        mine_row= rand() % (BOARDSIZE -2) +1;
        mine_col= rand() % (BOARDSIZE -2) +1;

        if(mines_board[mine_row][mine_col]!='*'){
            mines_board[mine_row][mine_col]='*';
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

void increment (int row, int column){

    if( mines_board[row][column] != ' ' && mines_board[row][column] != '*' ){
        mines_board[row][column]++;
    }
    return;
}

void print_mines_board(){

    int iterator1;
    int iterator2;

    for(iterator1=0 ; iterator1< BOARDSIZE-1 ; iterator1++){

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
        for(iterator2 = 0; iterator2 < BOARDSIZE; iterator2++){
            printf(" %c ", mines_board[iterator1][iterator2]);
        }
        if(iterator1 != 0){
            printf("  %d\n", iterator1);
        }
        else{
            printf("\n");
        }
    }
}


void build_player_board(){
    int iterator1;
    int iterator2;


      for(iterator1=0 ; iterator1 < BOARDSIZE ; iterator1++){
        for(iterator2=0; iterator2 < BOARDSIZE ; iterator2++){
            if(iterator1==0 || iterator1==BOARDSIZE-1){
                player_board[iterator1][iterator2]=' ';
            }
            else if(iterator2==0 || iterator2== BOARDSIZE-1){
                player_board[iterator1][iterator2]=' ';
            }

            else{
                player_board[iterator1][iterator2]='-';
            }
        }
    }

}

void build_solver_chance_board(){
    int iterator1;
    int iterator2;

     for(iterator1=0 ; iterator1 < BOARDSIZE ; iterator1++){
        for(iterator2=0; iterator2 < BOARDSIZE ; iterator2++){
            if(iterator1==0 || iterator1==BOARDSIZE-1){
                solver_chance_board[iterator1][iterator2]=-1;
            }
            else if(iterator2==0 || iterator2== BOARDSIZE-1){
                solver_chance_board[iterator1][iterator2]=-1;
            }

            else{
                solver_chance_board[iterator1][iterator2]=60;
            }
        }
    }

}

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

void look_for_mines(int row, int column){

    int    coordinates_row[]={0, 0, 1, -1, -1, -1, 1, 1};
    int coordinates_column[]={1, -1, 0, 0, -1, 1, -1, 1};

    int hidden_spaces = 0;
    int mines = 0;

    int iterator1 = 0;
    int iterator2 = 0;

    int player_board_number = (int)(player_board[row][column] - '0');

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

    if(hidden_spaces==0){
        return;
    }
    iterator1 = 0;
    iterator2 = 0;
    if( (mines == player_board_number) && (hidden_spaces != 0) ){
        while(iterator1 <= 7){
            if(player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] == '-'){
                reveal_spaces(row+coordinates_row[iterator1], column+coordinates_column[iterator2]);
            }
            iterator1++;
            iterator2++;
        }
    }
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

void automatic_flagging(){
    int iterator1;
    int iterator2;

    for( iterator1 = 1; iterator1 < BOARDSIZE -1; iterator1++){
        for( iterator2 = 1; iterator2 < BOARDSIZE -1; iterator2++){
            if( player_board[iterator1][iterator2] >= '1' && player_board[iterator1][iterator2] <= '9'){
                look_for_mines(iterator1, iterator2);
            }
        }
    }

    print_player_board();

}

void automatic_chance_placer(){
    int iterator1;
    int iterator2;

    for( iterator1 = 1; iterator1 < BOARDSIZE -1; iterator1++){
        for( iterator2 = 1; iterator2 < BOARDSIZE -1; iterator2++){
            if(player_board[iterator1][iterator2] == '-'){
                    place_chance(iterator1, iterator2);
            }
        }
    }

}

void place_chance(int row, int column){

    solver_chance_board[row][column] = 0;

    int    coordinates_row[]={0, 0, 1, -1, -1, -1, 1, 1};
    int coordinates_column[]={1, -1, 0, 0, -1, 1, -1, 1};

    int iterator1 = 0;
    int iterator2 = 0;

    while(iterator1 <= 7){
        if( player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] >= '1'
           && player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] <= '9'){
            solver_chance_board[row][column] += (int)(player_board[row+coordinates_row[iterator1]][column+coordinates_column[iterator2]] - '0' );
        }
        iterator1++;
        iterator2++;
    }

}

void automatic_decision_taker(){
    int iterator1;
    int iterator2;

    int iterator1_minimum_chance = 0;
    int iterator2_minimum_chance = 0;
    int minimum_chance_recorded = 55;

    for( iterator1 = 1; iterator1 < BOARDSIZE -1; iterator1++){
        for( iterator2 = 1; iterator2 < BOARDSIZE -1; iterator2++){
            if(player_board[iterator1][iterator2] == '-' && solver_chance_board[iterator1][iterator2] < minimum_chance_recorded){
                 iterator1_minimum_chance = iterator1;
                 iterator2_minimum_chance = iterator2;
            }
        }
    }

    reveal_spaces(iterator1_minimum_chance, iterator2_minimum_chance);

    print_player_board();
    print_solver_chance_board();

}


void print_player_board(){

    int iterator1;
    int iterator2;

    for(iterator1=0 ; iterator1< BOARDSIZE-1 ; iterator1++){

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
        for(iterator2 = 0; iterator2 < BOARDSIZE; iterator2++){
            printf(" %c ", player_board[iterator1][iterator2]);
        }
        if(iterator1 != 0){
            printf("  %d\n", iterator1);
        }
        else{
            printf("\n");
        }
    }
}

void reveal_spaces (int row, int column){


        if(mines_board[row][column]==' '){
            return;
        }

        player_board[row][column]=mines_board[row][column];


        if(mines_board[row][column] == '0'){
            mines_board[row][column]= '~';
            player_board[row][column]='~';
            reveal_spaces(row+1,column);
            reveal_spaces(row-1,column);
            reveal_spaces(row,column+1);
            reveal_spaces(row,column-1);
            reveal_spaces(row+1,column+1);
            reveal_spaces(row+1,column-1);
            reveal_spaces(row-1,column+1);
            reveal_spaces(row-1,column-1);

        }

    solver_chance_board[row][column] = 59;

    if(player_board[row][column]== '*'){
            loss();
            return;
        }

}

void loss(){
    char answer;

    print_mines_board();

    printf("\n");

    print_solver_chance_board();

    printf("\nYou're dead. Sorry :)");
    printf("\nWanna try to live this time? (y/n)--> ");
    scanf(" %c", &answer);

    if(answer == 'y'){
        system("cls");
        start_game();
    }
    else
        exit(0);
}

void win()
{
    char answer;

    printf("\n You got to live until the end. Good job! :)");
    printf("\nWanna try to die this time? (y/n)--> ");
    scanf(" %c", &answer);

    if(answer == 'y'){
        system("cls");
        start_game();
    }
    else
        exit(0);

}

int check_win(){
    int iterator1;
    int iterator2;

    for(iterator1 = 1; iterator1 < BOARDSIZE-1 ; iterator1++){
        for(iterator2 = 1; iterator2 < BOARDSIZE-1 ; iterator2++) {
            if(player_board[iterator1][iterator2] == '-' && mines_board[iterator1][iterator2] != '*'){
                return FALSE;
            }
        }
    }

    return TRUE;
}

void start_game (){


    int row, column;


    // Build both mines and player boards
    build_mines_board();
    build_player_board();
    build_solver_chance_board();
    print_player_board();

    printf("Welcome to our minesweeper autosolver!\n");

    int first_move = 1;

    print_mines_board();

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


        if( first_move ){
            reveal_spaces( row, column);
        }
        first_move = 0;

        int x;
        scanf("%d", &x);
        if(x==1){
        automatic_flagging();
        automatic_chance_placer();
        automatic_decision_taker();

        //system("cls");

        print_player_board();

        printf("\n");
        //print_solver_chance_board();
        printf("\n");

        if(check_win() == TRUE){
            win();
        }

        }

    }

}

int main(){
    build_mines_board();


    puts("\n");
    system("pause");
    start_game();

    return 0;
}

