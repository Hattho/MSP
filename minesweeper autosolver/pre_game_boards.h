/**
 *  @file pre_game_boards.h
 *  @brief C library containing the headers of the functions that build and print the boards for the game .
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */

#ifndef MINESWEEPER_PRE_GAME__BOARDS_H
#define MINESWEEPER_PRE_GAME__BOARDS_H

void build_mines_board();
void increment (int row, int column);
void print_mines_board();
void build_player_board();
void print_player_board();


#endif //MINESWEEPER_PRE_GAME_BOARDS_H
