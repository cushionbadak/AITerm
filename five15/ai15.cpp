#include "ai15.h"

ai15::ai15()
{

}
ai15::~ai15()
{

}

int ai15::avalue3_w(board* brd)
{
	
	return 0;
}

int ai15::choice(board* brd, int color)
{


	return vsimplechoice(brd, color);
	return 0;
}

int ai15::vsimplechoice(board* brd, int color)
{
	//simple choice
	int iter1;
	int choice;
	std::vector<int> bbb = *brd->b;
	for (iter1 = 0; iter1 < SIZE*SIZE - 1; iter1++)
	{
		if (bbb.at(iter1) == EMPTY)
		{
			choice = iter1;
			return choice;
		}
	}
	return 0;
}