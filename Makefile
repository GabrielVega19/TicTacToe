CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o tictactoe.o
ALL: tictactoe_driver
tictactoe_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o tictactoe_driver $(OBJECTS)
main.o: Main.c
	$(CC) $(CFLAGS) -c Main.c -o main.o
tictactoe.o: TicTacToe.c
	$(CC) $(CFLAGS) -c TicTacToe.c -o tictactoe.o
clean:
	rm tictactoe_driver $(OBJECTS)
