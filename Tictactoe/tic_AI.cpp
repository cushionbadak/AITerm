#pragma once
#include "tic_AI.h"

tic_AI::tic_AI()
{

}
tic_AI::~tic_AI()
{

}

std::string tic_AI::bestChoice(std::vector<std::vector<int> > b, int color)
{
	int r1, r2;
	int iter1, iter2;
	r1 = -1; r2 = -1;
	

	//simpleChoice - default
	if (r1 == -1 && r2 == -1) return (simpleChoice(b));


	return addrToStr(r1, r2);


}

std::string tic_AI::addrToStr(int r, int i)
{
	std::string s;
	std::string temp;
	temp = i + 'A';
	s.append(temp);
	temp = r + '1';
	s.append(temp);

	return s;
}

std::string tic_AI::simpleChoice(std::vector<std::vector<int> > b)
{
	int iter1, iter2;
	int r1, r2;
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			if (b.at(iter1).at(iter2) == 0)
			{
				r1 = iter1; r2 = iter2;
				return addrToStr(r1, r2);
			}
		}
	}
}