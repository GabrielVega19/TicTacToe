#include <stdio.h>

struct tictactoe_public;
typedef struct tictactoe_public* TICTACTOE;

struct tictactoe_public {
	void (*print_state)(TICTACTOE hTTT);
	void (*destroy)(TICTACTOE* phTTT);
	void (*print_game)(TICTACTOE hTTT);
	void (*change_square)(TICTACTOE hTTT, char input, int num);
	int (*is_set)(TICTACTOE hTTT, int index);
	int (*squares_set)(TICTACTOE hTTT);
	int (*check_horizontal)(TICTACTOE hTTT, int index, char who_won);
};

TICTACTOE ttt_init_default(void); 




