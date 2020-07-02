#include <stdio.h>
#include <stdlib.h>
#include "TicTacToe.h"
#include <time.h>


char start(void);
void clear_keyboard_buffer(void);
void player_turn(TICTACTOE game, char player_char);
void computer_turn(TICTACTOE game, char computer_char);
char set_comp_char(char player_char);

void main(int argc, char* argv) {
	char player_char;
	char computer_char;
	TICTACTOE game;

	player_char = start();
	computer_char = set_comp_char(player_char);
	game = ttt_init_default();
	if (game == NULL) {
		exit(5);
	}
	game->print_game(game);

	while (game->squares_set(game) < 8) {
		player_turn(game, player_char);
		computer_turn(game, computer_char);
	}
	player_turn(game, player_char); 

	game->destroy(&game);

	return 0;
}

char start(void) {
	int x;
	char c;
	srand(time(0));

	printf("Welcome to TicTacToe Press 1 to start or 2 to quit: ");

	scanf("%d", &x);
	clear_keyboard_buffer();

	while (x != 1 && x != 2) {
		printf("Please press 1 to start or 2 to quit: ");
		scanf("%d", &x);
		clear_keyboard_buffer();
	}

	if (x == 2) {
		exit(0);
	}
	else {
		printf("Would you like to play as X or O: ");
		scanf("%c", &c);
		clear_keyboard_buffer();

		while (c != 'x' && c != 'o') {
			printf("Please enter X or O: ");
			scanf("%c", &c);
			clear_keyboard_buffer();
		}

		return c;
	}
}

void player_turn(TICTACTOE game, char player_char) {
	int num;

	printf("Enter a number between 1 and 9: ");
	scanf("%d", &num);
	clear_keyboard_buffer();

	while (num > 10 || num < 0 || game->is_set(game, num - 1)) {
		printf("Enter a number between 1 and 9: ");
		scanf("%d", &num);
		clear_keyboard_buffer();
	}

	game->change_square(game, player_char, num);
	game->print_game(game);
	if (check_for_win(game, num - 1, player_char)) {
		printf("Congradulations you won the game");
		exit(0);
	}
}

void clear_keyboard_buffer(void) {
	char c;

	scanf("%c", &c);
	while (c != '\n') {
		scanf("%c", &c);
	}
}

void computer_turn(TICTACTOE game, char computer_char) {
	int index;

	printf("Computer Turn\n");

	index = rand() % 3;
	while (game->is_set(game, index)) {
		index = rand() % 3;
	}

	game->change_square(game, computer_char, index + 1);
	game->print_game(game);
	if (check_for_win(game, index, computer_char)) {
		printf("You lost the game to the computer");
		exit(0);
	}
}

char set_comp_char(char player_char) {
	if (player_char == 'x') {
		return 'o';
	}
	else if (player_char == 'o') {
		return 'x';
	}
	else {
		printf("you fucked up getting the player char in set_comp_char");
		return '~';
	}
}

int check_for_win(TICTACTOE game, int index, char test_char) {
	if (game->check_horizontal(game, index, test_char)) {
		return 1;
	}
	else {
		return 0;
	}
}

