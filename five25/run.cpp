#include "game.h"

int main(void)
{
	game *five25 = new game();
	five25->start();
	five25->~game();

	return 0;
}