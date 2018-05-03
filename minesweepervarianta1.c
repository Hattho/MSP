
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define BOARDSIZE 13
#define NO_MINES 4
#define TRUE 1
#define FALSE 0

char mines_board[BOARDSIZE][BOARDSIZE];
char player_board[BOARDSIZE][BOARDSIZE];

void build_mines_board(){

    int iterator1;
    int iterator2;
    int i,j;
    int mine_row;
    int mine_col;

    for(iterator1=0 ; iterator1 < BOARDSIZE ; iterator1++){
        for(iterator2=0; iterator2 < BOARDSIZE ; iterator2++){
            if(iterator1==1 || iterator1==BOARDSIZE-2){
                mines_board[iterator1][iterator2]=' ';
            }
            else if(iterator2==1 || iterator2== BOARDSIZE-2){
                mines_board[iterator1][iterator2]=' ';
            }
            else if( iterator1==0 || iterator1==BOARDSIZE-1 ){
                for(j = 2;j <= BOARDSIZE-3; j++){
                    mines_board[iterator1][j]=(char)(((int)'0')+j-1);
                }
            }
            else if( iterator2==0 || iterator2==BOARDSIZE-1 ){
                for(i = 2;i <= BOARDSIZE-3; i++){
                    mines_board[i][iterator2]=(char)(((int)'0')+i-1);
                }
            }
            else{
                mines_board[iterator1][iterator2]='0';
            }
        }
    }

    srand(time(NULL));

     iterator1=1;
     while(iterator1<=NO_MINES){
        mine_row= rand() % (BOARDSIZE -4) +2;
        mine_col= rand() % (BOARDSIZE -4) +2;

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
    int iterator1, iterator2;

    for(iterator1 = 0; iterator1 < BOARDSIZE; iterator1++){
        for(iterator2 = 0; iterator2 < BOARDSIZE; iterator2++){
            printf("%c ", mines_board[iterator1][iterator2]);
        }
        printf("\n");
    }
}


void build_player_board(){
    int iterator1;
    int iterator2;
    int i,j;

    for(iterator1=0;iterator1<BOARDSIZE;iterator1++){
        for(iterator2=0; iterator2<BOARDSIZE ; iterator2++){
            if(iterator1==1 || iterator1==BOARDSIZE-2){
                player_board[iterator1][iterator2]=' ';
            }
            else if(iterator2==1 || iterator2== BOARDSIZE-2){
                    player_board[iterator1][iterator2]=' ';
            }
            else if( iterator1==0 || iterator1==BOARDSIZE-1 ){
                for(j = 2;j <= BOARDSIZE-3; j++){
                    player_board[iterator1][j]=(char)(((int)'0')+j-1);
                }
            }
            else if( iterator2==0 || iterator2==BOARDSIZE-1 ){
                for(i = 2;i <= BOARDSIZE-3; i++){
                    player_board[i][iterator2]=(char)(((int)'0')+i-1);
                }
            }
            else{
                player_board[iterator1][iterator2]='-';
            }
        }
    }

}

void print_player_board(){

    int iterator1, iterator2;

    for(iterator1 = 0; iterator1 < BOARDSIZE; iterator1++){
        for(iterator2 = 0; iterator2 < BOARDSIZE; iterator2++){
            printf("%c ", player_board[iterator1][iterator2]);
        }
        printf("\n");
    }
}

void reveal_spaces (int row, int column){

        if(mines_board[row][column]==' '){
            return;
        }

        player_board[row][column]=mines_board[row][column];

        if(mines_board[row][column] == '0'){
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

int find_nearby_mines(int row, int column){
    int mines = 0;


    if(mines_board[row - 1][column] == '*')
        mines++;
    if(mines_board[row + 1][column] == '*')
        mines++;
    if(mines_board[row][column - 1] == '*')
        mines++;
    if(mines_board[row][column + 1] == '*')
        mines++;


    if(mines_board[row - 1][column + 1] == '*')
        mines++;
    if(mines_board[row - 1][column - 1] == '*')
        mines++;
    if(mines_board[row + 1][column + 1] == '*')
        mines++;
    if(mines_board[row + 1][column - 1] == '*')
        mines++;

    return mines;
}

void loss(){
    char answer;

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

    for(iterator1 = 2; iterator1 < BOARDSIZE - 2; iterator1++){
        for(iterator2 = 2; iterator2 < BOARDSIZE - 2; iterator2++) {
            if(player_board[iterator1][iterator2] == '-' && mines_board[iterator1][iterator2] != '*'){
                return FALSE;
            }
        }
    }

    return TRUE;
}

void start_game (){


 int row, column;

    // Build both game boards
    build_mines_board();
    build_player_board();
    print_player_board();

    for(;;){
        do {
        printf("Choose your doom:\n");
        printf("Row: ");
        scanf("%d", &row);
        printf("Column: ");
        scanf("%d", &column);
        } while(row < 2 || row > BOARDSIZE - 3 || column < 2 || column > BOARDSIZE - 3);


        if(mines_board[row+1][column+1] == '*'){
            printf("We told you that you'll die :)\n");
            print_mines_board();
            loss();
        }
        else{
            reveal_spaces(row+1, column+1);
        }
        //system("cls");
        print_player_board();

        if(check_win() == TRUE)
            win();

    }
}

int main(){
    build_mines_board();
    print_mines_board();

    puts("\n");
    //system("pause");
    start_game();

    return 0;
}

