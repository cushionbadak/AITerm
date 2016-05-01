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
	int color = BLACK;
	int status = EMPTY;

	std::cout << "Game Start" << std::endl;
	while (status == EMPTY)
	{
		cur_b->board_print();
		turn(color);

		if (cur_l->black_win()) { status = BLACK; continue; }
		else if (cur_l->white_win()) { status = WHITE; continue; }
		else if (cur_b->is_board_full()) { break; }
		else { color = cur_b->reverse_color(color); }
	}
	cur_b->board_print();

	return 0;
}

int game::turn(int color)
{
	// each turn
	// status 0 : normal turn start
	// status 1 : Inappropriate input
	// status 2 : double-3 case input
	int status = 0;
	std::string user_input;
	int input_addr;
	do {
		turn_start(color, status);
		if (color_and_play(color))
		{
			// player plays
			std::cin >> user_input;
			input_addr = cur_b->str2addr(user_input);
			if (input_addr == -1) { status = 1; }
			else if (aiai->is_d3_wrap(cur_b, input_addr, color)) { status = 2; }
			else if (cur_b->set_board_safe(input_addr, color) != 0) { status = 1; }
			else
			{
				status = 0;
				cur_l->full_update(cur_b->brd);
			}
		}
		else
		{
			// AI plays
			// believe AI do not make inappropriate play
			std::cout << " <<AI THINKS>>" << std::endl;
			input_addr = aiai->pick(cur_b);
			cur_b->set_board_safe(input_addr, color);
			cur_l->full_update(cur_b->brd);
			std::cout << " AI puts : " << cur_b->addr2string(input_addr) << std::endl;
		}
	} while (status != 0);

	return 0;
}

int game::turn_start(int color, int status)
{
	// turn start message
	// status 0 : normal turn start
	// status 1 : Inappropriate input
	// status 2 : double-3 case input
	// default : inappropriate function call. returns -1
	// if inappropriate color input comes, it returns -2
	// normally, it returns 0
	if (color != BLACK && color != WHITE) return -2;
	else switch (status)
	{
	case 0:
		if (color == BLACK) { std::cout << " BLACK TURN !" << std::endl << " BLACK INPUT : "; }
		else { std::cout << " WHITE TURN !" << std::endl << " WHITE INPUT : "; }
		break;
	case 1:
		if (color == BLACK) { std::cout << " Inappropriate Input. Write again !" << std::endl << " BLACK INPUT : "; }
		else { std::cout << " Inappropriate Input. Write again !" << std::endl << " WHITE INPUT : "; }
		break;
	case 2:
		if (color == BLACK) { std::cout << " It's DOUBLE THREE, Write Again !" << std::endl << " BLACK INPUT : "; }
		else { std::cout << " It's DOUBLE THREE, Write Again !" << std::endl << " WHITE INPUT : "; }
		break;
	default:
		std::cout << "WARNING : game - turn_start - inappropriate status" << std::endl;
		return -1;
	}
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
	std::string a;
	game g = game();

	// game start
	g.game_start();
	a = std::cin.get();
	
	return 0;
}
