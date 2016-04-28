#include <iostream>
#include <string>
#include "game.h"

game::game()
{
	bef_l = new lines();
	cur_l = new lines();
	bef_b = new board();
	cur_b = new board();
}

game::~game()
{
	bef_l->~lines();
	cur_l->~lines();
	bef_b->~board();
	cur_b->~board();
}

int game::game_start(void)
{
	std::cout << "hello" << std::endl;
	return 0;
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
