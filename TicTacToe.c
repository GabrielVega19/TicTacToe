#include <stdio.h>
#include <stdlib.h>
#include "TicTacToe.h"
#include <string.h>

struct tictactoe_private {
	//public stuff
	void (*print_state)(TICTACTOE hTTT);
	void (*destroy)(TICTACTOE* phTTT);
	void (*print_game)(TICTACTOE hTTT);
	void (*change_square)(TICTACTOE hTTT, char input, int num);
	int (*is_set)(TICTACTOE hTTT, int index);
	int (*squares_set)(TICTACTOE hTTT);
	int (*check_horizontal)(TICTACTOE hTTT, int index, char* who_won);

	//private stuff
	char* state;
	int num_squares_set;
};
typedef struct tictactoe_private TicTacToe;


void print_state(TICTACTOE hTTT);
void destroy(TICTACTOE* phTTT);
void print_game(TICTACTOE hTTT);
void change_square(TICTACTOE hTTT, char input, int num);
char upper(char input);
int is_set(TICTACTOE hTTT, int index);
int squares_set(TICTACTOE hTTT);
int row_win(TicTacToe* pTTT, int min, int max, char c);
int check_horizontal(TICTACTOE hTTT, int index, char who_won);


TICTACTOE ttt_init_default(void) {
	TicTacToe* pTTT = (TicTacToe*)malloc(sizeof(TicTacToe));

	if (pTTT != NULL) {
		pTTT->state = (char*)malloc(sizeof(char) * 9);
		if (pTTT->state == NULL) {
			free(pTTT);
			printf("Could not malloc state");
			exit(1);
		}

		pTTT->print_state = print_state;
		pTTT->destroy = destroy;
		pTTT->print_game = print_game;
		pTTT->change_square = change_square;
		pTTT->is_set = is_set;
		pTTT->squares_set = squares_set;
		pTTT->check_horizontal = check_horizontal;
		
		pTTT->num_squares_set = 0;
		for (int i = 0; i < 9; i++) {
			pTTT->state[i] = '-';
		}
	}

	return (TICTACTOE)pTTT;
}

void print_state(TICTACTOE hTTT) {
	TicTacToe* pTTT = (TicTacToe*)hTTT;
	
	for (int i = 0; i < 9; i++) {
		printf("%c, ", pTTT->state[i]);
	}
	printf("\n");

	return;
}

void destroy(TICTACTOE* phTTT) {
	TicTacToe* pTTT = (TicTacToe*)*phTTT;

	if (pTTT != NULL) {
		free(pTTT->state);
		free(pTTT);
	}

	*phTTT = NULL;

	return;
}

void print_game(TICTACTOE hTTT) {
	TicTacToe* pTTT = (TicTacToe*)hTTT;


	for (int i = 0; i < 7; i += 3) {
		printf("     |     |     \n");
		
		printf("  %c  |  %c  |  %c  \n", pTTT->state[i], pTTT->state[i + 1], pTTT->state[i + 2]);
		
		if (i < 4) {
			printf("_____|_____|_____\n");
		}
		else {
			printf("     |     |     \n");
		}
	}

	return;
}

void change_square(TICTACTOE hTTT, char input, int num) {
	TicTacToe* pTTT = (TicTacToe*)hTTT;

	pTTT->state[num - 1] = upper(input);
	pTTT->num_squares_set++;

	return;
}

char upper(char input) {
	if (input == 'o') {
		return 'O';
	}
	else if (input == 'x') {
		return 'X';
	}
	else {
		printf("You fucked up getting the play_char");
		return '~';
	}
}

int is_set(TICTACTOE hTTT, int index) {
	TicTacToe* pTTT = (TicTacToe*)hTTT;
	
	if (pTTT->state[index] == '-') {
		return 0;
	}
	else if (pTTT->state[index] == 'X' || pTTT->state[index] == 'O') {
		return 1;
	}
	else {
		return -999;
	}
}

int squares_set(TICTACTOE hTTT) {
	TicTacToe* pTTT = (TicTacToe*)hTTT;

	return pTTT->num_squares_set;
}

int check_horizontal(TICTACTOE hTTT, int index, char who_won) {
	TicTacToe* pTTT = (TicTacToe*)hTTT;
	
	//check row 1
	if (index >= 0 && index <= 2) {
		//check for win
		return row_win(pTTT, 0, 2, who_won);
	}

	//check row 2
	else if (index >= 3 && index <= 5) {
		//check for win
		return row_win(pTTT, 3, 5, who_won);
	}

	//check row 3
	else if (index >= 6 && index <= 8) {
		//check for win
		return row_win(pTTT, 6, 8, who_won);
	}

	else {
		printf("Invalid index in check_horizontal");
		return -99999;
	}
}

int row_win(TicTacToe* pTTT, int min, int max, char test_char) {
	int win = 1;
	test_char = upper(test_char);

	for (int i = min; i <= max; i++) {
		if (pTTT->state[i] != test_char) {
			win = 0;
		}
	}
	return win;
}