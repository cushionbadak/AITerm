#include "ai25.h"

ai25::ai25()
{

}
ai25::~ai25()
{

}

int ai25::choice(board* brd, int color)
{
	int a = achoice(brd, color);
	if (a != -1)
	{
		return a;
	}


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
	std::vector<std::tuple<int, int>> all;
	int iter1;
	int othercolor = brd->otherColor(color) - 1;
	
	// if board is empty
	if (brd->isEmpty())
	{
		return (SIZE*SIZE / 2);
	}
	
	all = acheck(brd);
	
	// if black has four stones
	for (iter1 = 0; iter1 < (int)all.size(); iter1++)
	{
		if (std::get<0>(all.at(iter1)) == 4)
		{
			return get1addr4(iter1, brd);
		}
	}

	// if white has four stones 
	for (iter1 = 0; iter1 < (int)all.size(); iter1++)
	{
		if (std::get<1>(all.at(iter1)) == 4)
		{
			return get1addr4(iter1, brd);
		}
	}
	//default value
	return -1;
}



std::vector<std::tuple<int, int>> ai25::acheck(board *brd)
{
	//TODO
	int iter1;

	std::vector<std::tuple<int, int>> horizontal_value, vertical_value, slash_value, backslash_value, all;

	horizontal_value = getHvalue(brd);
	vertical_value = getVvalue(brd);
	slash_value.push_back(getSvalue(brd));
	backslash_value.push_back(getBvalue(brd));

	for (iter1 = 0; iter1 < 5; iter1++)
	{
		all.push_back(horizontal_value.at(iter1));
	}
	for (iter1 = 0; iter1 < 5; iter1++)
	{
		all.push_back(vertical_value.at(iter1));
	}
	all.push_back(slash_value.at(0));
	all.push_back(backslash_value.at(0));

	return all;
}
int ai25::get1addr4(int addr, board *brd)
{
	int iter1;
	switch (addr)
	{
	//horizontal
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		for (iter1 = 0; iter1 < SIZE; iter1++)
		{
			if (brd->b->at(SIZE * addr + iter1) == EMPTY)
			{
				return SIZE*addr + iter1;
			}
		}
		break;

	//vertical
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		for (iter1 = 0; iter1 < SIZE; iter1++)
		{
			if (brd->b->at(addr + iter1*SIZE) == EMPTY)
			{
				return addr + iter1 * SIZE;
			}
		}
		break;

	//backslash
	case 10:
		for (iter1 = 0; iter1 < SIZE; iter1++)
		{
			if (brd->b->at(iter1*(SIZE + 1)) == EMPTY)
			{
				return iter1*(SIZE + 1);
			}
		}
		break;

	//slash
	case 11:
		for (iter1 = 0; iter1 < SIZE; iter1++)
		{
			if (brd->b->at(iter1*(SIZE - 1) + 4) == EMPTY)
			{
				return iter1*(SIZE - 1) + 4;
			}
		}
		break;

	//default
	default:
		return -1;
	}

	//default
	return -1;
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
	temp1 = 0; temp2 = 0;
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
	temp1 = 0; temp2 = 0;
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
	for (iter1 = 0; iter1 < (int)a.size(); iter1++)
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
	return result;
}
std::vector<std::tuple<int, int>> ai25::valueSort_w(std::vector<std::tuple<int, int>> a)
{
	//TODO
	std::vector<std::tuple<int, int>> result;
	std::tuple<int, int> temp;
	int iter1, iter2;
	for (iter1 = 0; iter1 < (int)a.size(); iter1++)
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
	return result;
}
std::vector<int> ai25::vSort_b(std::vector<std::tuple<int, int>> values)
{
	std::vector<int> a;
	int iter1, iter2, temp;
	for (iter1 = 0; iter1 < (int)values.size(); iter1++)
	{
		a.push_back(iter1);
		for (iter2 = iter1; iter2 > 0; iter2--)
		{
			if (std::get<0>(values.at(a.at(iter2))) < std::get<0>(values.at(a.at(iter2 - 1))))
			{
				temp = a.at(iter2);
				a.at(iter2) = a.at(iter2 - 1);
				a.at(iter2 - 1) = temp;
			}
		}
	}
	return a;
}
std::vector<int> ai25::vSort_w(std::vector<std::tuple<int, int>> values)
{
	std::vector<int> a;
	int iter1, iter2, temp;
	for (iter1 = 0; iter1 < (int)values.size(); iter1++)
	{
		a.push_back(iter1);
		for (iter2 = iter1; iter2 > 0; iter2--)
		{
			if (std::get<1>(values.at(a.at(iter2))) < std::get<1>(values.at(a.at(iter2 - 1))))
			{
				temp = a.at(iter2);
				a.at(iter2) = a.at(iter2 - 1);
				a.at(iter2 - 1) = temp;
			}
		}
	}
	return a;
}
int ai25::getMax_b(std::vector<std::tuple<int, int, int>> values)
{
	int iter1;
	int max = 0;
	int temp;
	for (iter1 = 0; iter1 < (int)values.size(); iter1++)
	{
		temp = std::get<1>(values.at(iter1));
		if (temp > max)
		{
			max = temp;
		}
	}
	return max;
}
int ai25::getMax_w(std::vector<std::tuple<int, int, int>> values)
{
	int iter1;
	int max = 0;
	int temp;
	for (iter1 = 0; iter1 < (int)values.size(); iter1++)
	{
		temp = std::get<2>(values.at(iter1));
		if (temp > max)
		{
			max = temp;
		}
	}
	return max;
}

int ai25::getnummax_b(std::vector<std::tuple<int, int, int>> values, int max)
{
	//TODO
	return 0;
}

int ai25::getnummax_w(std::vector<std::tuple<int, int, int>> values, int max)
{
	//TODO
	return 0;
}