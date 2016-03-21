#pragma once
#include "game.h"

int main(void)
{
	game h = game();
	h.start();
	h.~game();
	return 0;
}