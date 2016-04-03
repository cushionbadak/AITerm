#include "ai25.h"

ai25::ai25()
{

}
ai25::~ai25()
{

}
int ai25::choice(board* brd, int color)
{
	//simple choice
	int iter1;
	int choice;
	std::vector<int> bbb = *brd->b;
	for (iter1 = 0; iter1 < SIZE*SIZE - 1; iter1++)
	{
		if (bbb.at(iter1 + 1) == EMPTY) 
		{
			choice = iter1 + 1;
			return choice;
		}
		else if(bbb.at(iter1) == BLACK)
		{
			bbb.at(iter1) = WHITE;
		}
	}
	return 0;
}