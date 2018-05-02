
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define BOARDSIZE 13
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
                mines_board[iterator1][iterator2]='o';
            }
        }
    }

    srand(time(NULL));

     iterator1=1;
     while(iterator1<=10){
        mine_row= rand() % (BOARDSIZE -2) +1;
        mine_col= rand() % (BOARDSIZE -2) +1;

        if(mines_board[mine_row][mine_col]=='o'){
            mines_board[mine_row][mine_col]='*';
            iterator1++;
        }
     }


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

int find_nearby_mines(int row, int col)
{
    int mines = 0;


    if(mines_board[row - 1][col] == '*')
        mines++;
    if(mines_board[row + 1][col] == '*')
        mines++;
    if(mines_board[row][col - 1] == '*')
        mines++;
    if(mines_board[row][col + 1] == '*')
        mines++;


    if(mines_board[row - 1][col + 1] == '*')
        mines++;
    if(mines_board[row - 1][col - 1] == '*')
        mines++;
    if(mines_board[row + 1][col + 1] == '*')
        mines++;
    if(mines_board[row + 1][col - 1] == '*')
        mines++;

    return mines;
}

int main(){

    build_mines_board();

    print_mines_board();

    printf("\n");

    build_player_board();

    print_player_board();


    return 0;
}

