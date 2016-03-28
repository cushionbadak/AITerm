#pragma once
#include "game.h"

int main(void)
{
	game h = game();
	h.start();
	h.~game();
	std::cin.get();
	return 0;
}