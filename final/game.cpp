#include <iostream>
#include <string>
#include "game.h"

game::game()
{
	//bef_l = new lines();
	cur_l = new lines();
	//bef_b = new board();
	cur_b = new board();
	aiai = new ai();

	// 0 is ai
	// 1 is player
	black_play = 0;
	white_play = 1;
}

game::~game()
{
	//bef_l->~lines();
	cur_l->~lines();
	//bef_b->~board();
	cur_b->~board();
	aiai->~ai();
}

int game::game_start(void)
{
	// game start ! -- The Main Flow of the renju game.
	// status = EMPTY : normal state
	// status = BLACK : BLACK win state
	// status = WHITE : WHITE win state
	// when draw, status has EMPTY value
	/*
	int color = BLACK;
	int status = EMPTY;

	while (status == EMPTY)
	{
		turn(color);

		if (cur_l->black_win()) { status = BLACK; continue; }
		else if (cur_l->white_win()) { status = WHITE; continue; }
		else if (cur_b->is_board_full()) { break; }
		else { color = cur_b->reverse_color(color); }
	}
	cur_b->board_print();
	*/
	std::string input_string;
	int color = BLACK;
	int status = EMPTY;
	int flag = 0;
	std::cin >> input_string;
	if (input_string.compare("START") == 0)
	{
		black_play = 0;
		white_play = 1;
	}
	else
	{
		black_play = 1;
		white_play = 0;
	}
	//while (status == EMPTY)
	while (1)
	{
		turn(color, input_string, flag);
		if (cur_l->black_win()) { status = BLACK; continue; }
		else if (cur_l->white_win()) { status = WHITE; continue; }
		else if (cur_b->is_board_full()) { break; }
		else { color = cur_b->reverse_color(color); }
		
		// after color changed
		flag = 1;
		if (color_and_play(color)) { std::cin >> input_string; }
	}

	return 0;
}

int game::turn(int color, std::string input_string, int flag)
{
	// each turn
	// status 0 : normal turn start
	// status 1 : Inappropriate input
	// status 2 : double-3 case input
	int status = 0;
	int input_addr;

	if (color_and_play(color))
	{
		// enemy (player)
		input_addr = cur_b->str2addr(input_string);
		cur_b->set_board_safe(input_addr, color);
		cur_l->full_update(cur_b->brd);
	}
	else
	{
		// self (ai)
		input_addr = aiai->pick(cur_b, color);
		cur_b->set_board_safe(input_addr, color);
		cur_l->full_update(cur_b->brd);
		
		std::cout << cur_b->addr2string(input_addr) << std::endl;
	}
	return 0;
}

int game::turn_start(int color, int status)
{
	return 0;
}

int game::color_and_play(int color)
{
	// gives whether input color's player is ai or player
	//if inappropriate color comes, return -1
	if (color == BLACK) return black_play;
	else if (color == WHITE) return white_play;
	else return -1;
}

// main function
int main(void)
{
	game g = game();

	// game start
	g.game_start();

	return 0;
}
