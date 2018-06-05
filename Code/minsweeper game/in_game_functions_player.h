/**
 *  @file in_game_functions_player.h
 *  @brief C library containing the headers of the functions used during the game itself.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */

#ifndef MINESWEEPER_IN_GAME_FUNCTIONS_PLAYER_H
#define MINESWEEPER_IN_GAME_FUNCTIONS_PLAYER_H

void reveal_spaces (int row, int column);
void loss();
void win();
int check_win();
void start_game();

#endif  MINESWEEPER_IN_GAME_FUNCTIONS_PLAYER_H
