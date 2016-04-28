#include "board.h"

board::board()
{
	brd = new bb(BRDSIZE*BRDSIZE);
}

board::~board()
{
	brd->~vector();
}

int board::color_sanity(int color)
{
	// if color is EMPTY or BLACK or WHITE, return 1. Otherwise, return 0.
	if (color == EMPTY || color == BLACK || color == WHITE) return 1;
	else return 0;
}

int board::addr_sanity(int addr)
{
	// if addr is in brd's size, return 1.
	// Otherwise, return 0
	if (addr >= 0 && addr < brd->size())
	{
		return 1;
	}
	return 0;
}

int board::set_board(int addr, int color)
{
	// set board.

	// if addr_sanity fails, do not change board and return -2.
	// if color_sanity fails, return -1.
	// if board changed, return 0

	if (!addr_sanity(addr))	return -2;
	else if (!color_sanity(color)) return -1;
	else
	{
		brd->at(addr) = color;
		return 0;
	}
}

int board::set_board_safe(int addr, int color)
{
	// set board if and only if brd->at(addr) == EMPTY

	// if addr_sanity fails, do not change board and return -2.
	// if color_sanity fails, return -1.
	// if board not changed, return 1.
	// if board changed, return 0

	if (!addr_sanity(addr))	return -2;
	else if (!color_sanity(color)) return -1;
	else if (brd->at(addr) != EMPTY) return 1;
	else
	{
		brd->at(addr) = color;
		return 0;
	}
}

int board::is_board_full()
{
	//if board full, return 1
	//else, return 0
	int i;
	for (i = 0; i < BRDSIZE * BRDSIZE; i++) if (brd->at(i) == EMPTY) return 0;
	return 1;
}