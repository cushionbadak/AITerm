#include "ai25.h"

ai25::ai25()
{

}
ai25::~ai25()
{

}

int ai25::choice(board* brd, int color)
{
	return achoice(brd, color);


	//very simple choice - select first empty space
	return vsimplechoice(brd, color);
}
int ai25::vsimplechoice(board* brd, int color)
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

int ai25::achoice(board* brd, int color)
{
	std::vector<std::tuple<int, int>> horizontal_value;
	std::vector<std::tuple<int, int>> vertical_value;
	std::vector<std::tuple<int, int>> slash_value;
	std::vector<std::tuple<int, int>> backslash_value;

	std::vector<std::tuple<int, int>> t1, t2, t3, t4;
	int i1, i2, i3, i4;
	i1 = 0; i2 = 0; i3 = 0; i4 = 0;

	horizontal_value = getHvalue(brd);
	vertical_value = getVvalue(brd);
	slash_value.push_back(getSvalue(brd));
	backslash_value.push_back(getBvalue(brd));

	if (color == BLACK)
	{

	}
	else if (color == WHITE)
	{

	}
	else
	{

	}

}

std::vector<std::tuple<int, int>> ai25::getHvalue(board*brd)
{
	std::vector<std::tuple<int, int>> a;
	int iter1, iter2;
	int temp1, temp2;
	int tt;
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		temp1 = 0; temp2 = 0;
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			tt = SIZE * iter1 + iter2;
			if (brd->b->at(tt) == BLACK)
			{
				temp1++;
			}
			else if(brd->b->at(tt) == WHITE)
			{
				temp2++;
			}
		}
		a.push_back(calvalue(temp1, temp2));
	}
	return a;
}
std::vector<std::tuple<int, int>> ai25::getVvalue(board*brd)
{
	std::vector<std::tuple<int, int>> a;
	int iter1, iter2;
	int temp1, temp2;
	int tt;
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		temp1 = 0; temp2 = 0;
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			tt = iter1 + iter2 * SIZE;
			if (brd->b->at(tt) == BLACK)
			{
				temp1++;
			}
			else if (brd->b->at(tt) == WHITE)
			{
				temp2++;
			}
		}
		a.push_back(calvalue(temp1, temp2));
	}
	return a;
}
std::tuple<int, int> ai25::getSvalue(board*brd)
{
	int iter1;
	int temp1, temp2;
	int tt;
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		tt = iter1* (SIZE + 1);
		if (brd->b->at(tt) == BLACK)
		{
			temp1++;
		}
		else if (brd->b->at(tt) == WHITE)
		{
			temp2++;
		}
	}
	return calvalue(temp1, temp2);
}
std::tuple<int, int> ai25::getBvalue(board*brd)
{
	int iter1;
	int temp1, temp2;
	int tt;
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		tt = (iter1 + 1)* (SIZE - 1);
		if (brd->b->at(tt) == BLACK)
		{
			temp1++;
		}
		else if (brd->b->at(tt) == WHITE)
		{
			temp2++;
		}
	}
	return calvalue(temp1, temp2);
}

std::tuple<int, int> ai25::calvalue(int b, int w)
{
	if (b > 0 && w > 0)
	{
		return std::tuple<int, int>(0, 0);
	}
	else if (w == 0)
	{
		return std::tuple<int, int>(b, 0);
	}
	else
	{
		return std::tuple<int, int>(0, w);
	}
}

std::vector<std::tuple<int, int>> ai25::valueSort_b(std::vector<std::tuple<int, int>> a)
{
	//TODO
	std::vector<std::tuple<int, int>> result;
	std::tuple<int, int> temp;
	int iter1, iter2;
	for (iter1 = 0; iter1 < a.size(); iter1++)
	{
		result.push_back(a.at(iter1));
		for (iter2 = iter1; iter2 > 0; iter2--)
		{
			if (std::get<0>(result.at(iter2)) < std::get<0>(result.at(iter2 - 1)))
			{
				temp = result.at(iter2);
				result.at(iter2) = result.at(iter2 - 1);
				result.at(iter2 - 1) = result.at(iter2);
			}
		}
	}
}
std::vector<std::tuple<int, int>> ai25::valueSort_w(std::vector<std::tuple<int, int>> a)
{
	//TODO
	std::vector<std::tuple<int, int>> result;
	std::tuple<int, int> temp;
	int iter1, iter2;
	for (iter1 = 0; iter1 < a.size(); iter1++)
	{
		result.push_back(a.at(iter1));
		for (iter2 = iter1; iter2 > 0; iter2--)
		{
			if (std::get<1>(result.at(iter2)) < std::get<1>(result.at(iter2 - 1)))
			{
				temp = result.at(iter2);
				result.at(iter2) = result.at(iter2 - 1);
				result.at(iter2 - 1) = result.at(iter2);
			}
		}
	}
}