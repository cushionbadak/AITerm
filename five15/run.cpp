#include "game.h"

int main(void)
{
	game *five15 = new game();
	five15->start();
	five15->~game();

	std::cin.get();

	return 0;
}