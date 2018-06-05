/**
 *  @file in_game_functions_autosolver.h
 *  @brief C library containing the headers of the functions used by the autosolver during the game.
 *  @author Efrem Stefan and Hagiu Teodora
 *  @date 6/05/2018
 */

#ifndef MINESWEEPER_IN_GAME_FUNCTIONS_AUTOSOLVER_H
#define MINESWEEPER_IN_GAME_FUNCTIONS_AUTOSOLVER_H

void reveal_spaces(int row, int column);
void automatic_flagging();
void look_for_mines(int row, int column);
void automatic_chance_placer();
void place_chance(int row, int column);
void automatic_decision_taker();
void loss();
void win();
int check_win();
void start_game();

#endif //MINESWEEPER_IN_GAME_FUNCTIONS_AUTOSOLVER_H
