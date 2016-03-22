#pragma once
#include "tic_AI.h"

#define SIZE 3
#define WINLEN 3
#define DEPTH 3

tic_AI::tic_AI()
{

}
tic_AI::~tic_AI()
{
}

std::string tic_AI::bestChoice(brd b, int color)
{
	int r1, r2;
	int iter1, iter2;
	int blanksize;
	int temp1, temp2;
	int enemycolor;
	int score;
	//blank[2n - 2] : rowvalue of nth point
	//blank[2n - 1] : columnvalue of nth point
	std::vector<int> blanks;
	
	r1 = -1; r2 = -1;
	enemycolor = (color == 1) ? 2 : 1;

	//find blanks
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			if (b.at(iter1).at(iter2) == 0)
			{
				blanks.push_back(iter1);
				blanks.push_back(iter2);
			}
		}
	}
	blanksize = blanks.size();

	//win condition
	
	for (iter1 = 0; iter1 < blanksize / 2; iter1 = iter1 + 2)
	{
		brd *tempb;
		tempb = new brd(b);
		temp1 = blanks[iter1]; temp2 = blanks[iter1 + 1];

		//check win condition
		setBrd(tempb, temp1, temp2, color);
		if (win(*tempb, color))
		{
			return addrToStr(temp1, temp2);
		}
		tempb->clear();
	}
	//defeat condition
	for (iter1 = 0; iter1 < blanksize / 2; iter1 = iter1 + 2)
	{
		brd *tempb;
		tempb = new brd(b);
		temp1 = blanks[iter1]; temp2 = blanks[iter1 + 1];

		//check defeat condition
		setBrd(tempb, temp1, temp2, enemycolor);
		if (win(*tempb, enemycolor))
		{
			return addrToStr(temp1, temp2);
		}
		tempb->clear();
	}
	//others
	if (blanksize > 1) {
		score = 0;
		for (iter1 = 0; iter1 < blanksize / 2; iter1 = iter1 + 2)
		{
			brd *tempb;
			tempb = new brd(b);
			setBrd(tempb, temp1, temp2, color);

			if (score < getMyScore(DEPTH, (blanksize / 2), tempb, color, enemycolor))
			{
				r1 = blanks[iter1]; r2 = blanks[iter1 + 1];
			}
			tempb->clear();
		}
	}

	//simpleChoice - default
	/*
	if (r1 < 0 || r1 >= SIZE || r2 < 0 || r2 >= SIZE) return (simpleChoice(b));
	*/
	if (r1 < 0 || r1 >= SIZE || r2 < 0 || r2 >= SIZE) return (addrToStr(blanks[0], blanks[1]));

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

std::string tic_AI::simpleChoice(brd b)
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
	return addrToStr(0, 0);
}

int tic_AI::win(brd b, int color)
{
	//copy of "game.cpp" 's game::win(int color)
	int iter1, iter2, iter3;
	int temp;
	//horizontal search
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE - WINLEN + 1; iter2++)
		{
			temp = 1;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b.at(iter1).at(iter2 + iter3) != color) temp = 0;
			}
			if (temp) return 1;
		}
	}
	//vertical search
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE - WINLEN + 1; iter2++)
		{
			temp = 1;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b.at(iter2 + iter3).at(iter1) != color) temp = 0;
			}
			if (temp) return 1;
		}
	}
	//slash search
	for (iter1 = WINLEN - 1; iter1 < SIZE; iter1++)
	{
		for (iter2 = WINLEN - 1; iter2 < SIZE; iter2++)
		{
			temp = 1;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b.at(iter1 - iter3).at(iter2 - iter3) != color) temp = 0;
			}
			if (temp) return 1;
		}
	}
	//backslash search
	for (iter1 = WINLEN - 1; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE - WINLEN + 1; iter2++)
		{
			temp = 1;
			for (iter3 = 0; iter3 < WINLEN; iter3++)
			{
				if (b.at(iter1 - iter3).at(iter2 + iter3) != color) temp = 0;
			}
			if (temp) return 1;
		}
	}

	return 0;
}

void tic_AI::setBrd(brd *b, int r, int i, int color)
{
	if (r >= 0 && r < SIZE && i >= 0 && i < SIZE) b->at(r).at(i) = color;
}

int tic_AI::getMyScore(int depth, int blanksize, brd* b, int color, int enemycolor)
{
	if (depth == 0 || blanksize == 0) return 0;
	int currentscore = 0;
	int maxEnemy = 0;
	int tempscore;
	int iter1, iter2;
	std::vector<int> blanks;

	//make score

	//find blanks
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			if (b->at(iter1).at(iter2) == 0)
			{
				blanks.push_back(iter1);
				blanks.push_back(iter2);
			}
		}
	}
	//get maxEnemyScore
	for (iter1 = 0; iter1 < blanksize - 1; iter1 = iter1 + 2)
	{
		brd *tempb = new brd(*b);
		setBrd(b, blanks[iter1], blanks[iter1 + 1], enemycolor);
		tempscore = getMyScore(depth - 1, blanksize - 1, b, enemycolor, color);
		if (tempscore > maxEnemy)
		{
			maxEnemy = tempscore;
		}
		tempb->clear();
	}
	return (currentscore - maxEnemy);
}