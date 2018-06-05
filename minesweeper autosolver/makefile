CC=gcc

# -c = compilation
# -Wall = throws all warnings
CFLAGS=-c -Wall

all: minwsweeper_autsolver
# -c = compilation
# -Wall = throws all warnings
hanoi: autosolvermsp.o in_game_functions_autosolver.o pre_game_autosolver_boards.o pre_game_boards.o
	$(CC) autosolvermsp.o in_game_functions_autosolver.o pre_game_autosolver_boards.o pre_game_boards.o -o minesweeper_game

autosolvermsp.o: autosolvermsp.c
	$(CC) $(CFLAGS) autosolvermsp.c

in_game_functions_autosolver.o: in_game_functions_autosolver.c
	$(CC) $(CFLAGS) in_game_functions_autosolver.c

pre_game_autosolver_boards.o :pre_game_autosolver_boards.c
	$(CC) $(CFLAGS) pre_game_autosolver_boards.c

pre_game_boards.o :pre_game_boards.c
		$(CC) $(CFLAGS) pre_game_boards.c
