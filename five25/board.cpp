#include "board.h"

//const, dest
board::board()
{
	b = new std::vector<int>(SIZE * SIZE);
}
board::~board()
{
	b->~vector();
}

//int win (int color)
int board::win(int color)
{
	int iter1, iter2, iter3;
	int temp;
	//horizontal search
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE - WINLEN + 1; iter2++)
		{
			temp = 0;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b->at(iter1 * SIZE + iter2 + iter3) == color)
				{
					temp++;
					if (temp == WINLEN) return 1;
				}
			}
		}
	}
	//vertical search
	for (iter1 = 0; iter1 < SIZE - WINLEN + 1; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			temp = 0;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b->at(iter1 * SIZE + iter2 + iter3 * SIZE) == color)
				{
					temp++;
					if (temp == WINLEN) return 1;
				}
			}
		}
	}
	//slash search
	for (iter1 = WINLEN - 1; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE - WINLEN + 1; iter2++)
		{
			temp = 0;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b->at(iter1*SIZE + iter2 + iter3 * (SIZE - 1)) == color)
				{
					temp++;
					if (temp == WINLEN) return 1;
				}
			}
		}
	}
	//backslash search
	for (iter1 = 0; iter1 < SIZE - WINLEN + 1; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE - WINLEN + 1; iter2++)
		{
			temp = 0;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b->at(iter1*SIZE + iter2 + iter3 * (SIZE + 1)) == color)
				{
					temp++;
					if (temp == WINLEN) return 1;
				}
			}
		}
	}
	
	return 0;
}

//int threethree (int color)
int board::threethree(int color)
{

}

//int openfour(int color) __ TODO
int board::openfour(int color)
{
	return 0;
}
//int fourthree (int color) __ TODO
int board::fourthree(int color)
{
	return 0;
}