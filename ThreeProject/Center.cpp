#pragma once
#include <iostream>
#include "Board.h"
#include "Tictactoe.h"

int main()
{
	/*test code*/
	Board *b = new Board(3, 3, 5);
	b->test1();
	delete b;
	/*test code end*/

	return 0;
}