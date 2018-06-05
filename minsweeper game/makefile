CC=gcc

# -c = compilation
# -Wall = throws all warnings
CFLAGS=-c -Wall

all: minwsweeper
# -c = compilation
# -Wall = throws all warnings
hanoi: in_game_functions_player.o minwsweeper_game.o pre_game_boards.o
	$(CC) in_game_functions_player.o minwsweeper_game.o pre_game_boards.o -o minesweeper

in_game_functions_player.o: in_game_functions_player.c
	$(CC) $(CFLAGS) in_game_functions_player.c

minwsweeper_game.o: minwsweeper_game.c
	$(CC) $(CFLAGS) minwsweeper_game.c

pre_game_boards.o :pre_game_boards.c
	$(CC) $(CFLAGS) pre_game_boards.c
