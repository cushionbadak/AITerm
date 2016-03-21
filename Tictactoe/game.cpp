#pragma once
#include "game.h"

game::game()
{
	int iter1, iter2;
	b = new board();
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		row *temp = new row();
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			temp->push_back(0);
		}
		b->push_back(*temp);
		temp->clear();
	}
}

game::~game()
{
	b->clear();
}

void game::test1()
	{
		std::cout << "Hello, World!" << std::endl << std::endl;
	}

void game::start()
{
	//TODO : complete game start
	int gameEnd = 0;
	std::string input1, input2;
	tic_AI *ai = new tic_AI();

	setBoard("B2", 1);

	while (!gameEnd)
	{
		printBoard();
		
		//check if game ends.
		gameEnd = isGameEnd();
		if (gameEnd) break;

		std::cout << "Please input position of white stone: ";
		std::cin >> input1;
		if (input1 == "exit") break;
		if (!sanitycheck_input(input1))
		{
			std::cout << "Invalid Input." << std::endl << std::endl;
			continue;
		}
		setBoard(input1, 2);
		
		input2 = ai->bestChoice(*b, 1);
		setBoard(input2, 1);
		
	}
	ai->~tic_AI();
	std::cout << "End : Press Any Button." << std::endl;
	std::cin.get();
}

void game::printBoard()
{
	std::cout << "    A   B   C   " << std::endl;
	int iter;
	for (iter = SIZE; iter > 0; iter--)
	{
		std::cout << " " << printhelper(iter) << std::endl;
	}
	std::cout << "    A   B   C   " << std::endl << std::endl;
}

std::string game::printhelper(int i)
{
	std::string returnv;

	int t20 = b->at(2).at(0);
	int t21 = b->at(2).at(1);
	int t22 = b->at(2).at(2);
	int t10 = b->at(1).at(0);
	int t11 = b->at(1).at(1);
	int t12 = b->at(1).at(2);
	int t00 = b->at(0).at(0);
	int t01 = b->at(0).at(1);
	int t02 = b->at(0).at(2);

	switch (i)
	{
	case 3:
		//pre-
		returnv.append("3 ");
		//2, 0
		if (t20 != 0) returnv.append(getColorString(t20));
		else returnv.append("忙");
		//interval
		returnv.append("式");
		//2, 1
		if (t21 != 0) returnv.append(getColorString(t21));
		else returnv.append("成");
		//interval
		returnv.append("式");
		//2, 2
		if (t22 != 0) returnv.append(getColorString(t22));
		else returnv.append("忖");
		//post-
		returnv.append(" 3");
		break;

	case 2:
		//pre-
		returnv.append("2 ");
		//1, 0
		if (t10 != 0) returnv.append(getColorString(t10));
		else returnv.append("戍");
		//interval
		returnv.append("式");
		//1, 1
		if (t11 != 0) returnv.append(getColorString(t11));
		else returnv.append("托");
		//interval
		returnv.append("式");
		//1, 2
		if (t12 != 0) returnv.append(getColorString(t12));
		else returnv.append("扣");
		//post-
		returnv.append(" 2");
		break;

	case 1:
		//pre-
		returnv.append("1 ");
		//0, 0
		if (t00 != 0) returnv.append(getColorString(t00));
		else returnv.append("戌");
		//interval
		returnv.append("式");
		//0, 1
		if (t01 != 0) returnv.append(getColorString(t01));
		else returnv.append("扛");
		//interval
		returnv.append("式");
		//0, 2
		if (t02 != 0) returnv.append(getColorString(t02));
		else returnv.append("戎");
		//post-
		returnv.append(" 1");
		break;

	default:
		returnv.append("ERROR: game::printhelper");
	}
	return returnv;
}

std::string game::getColorString(int i)
{
	// i = 1  :  ≒ , black
	// i = 2  :  ∞ , white
	if (i == 1) return "≒";
	else if (i == 2) return "∞";
	else return " ";
}

int game::win(int color)
{
	//TODO

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
				if (b->at(iter1).at(iter2 + iter3) != color) temp = 0;
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
				if (b->at(iter2 + iter3).at(iter1) != color) temp = 0;
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
				if (b->at(iter1 - iter3).at(iter2 - iter3) != color) temp = 0;
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
				if (b->at(iter1 - iter3).at(iter2 + iter3) != color) temp = 0;
			}
			if (temp) return 1;
		}
	}

	return 0;
}

int game::boardfull(void)
{
	int iter1, iter2;
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		for (iter2 = 0; iter2 < SIZE; iter2++)
		{
			if (b->at(iter1).at(iter2) == 0) return 0;
		}
	}
	return 1;
}

int game::isGameEnd(void)
{
	int gameEnd = 0;
	if (win(1))
	{
		//black wins
		std::cout << "Black Wins!" << std::endl;
		gameEnd = 1;
	}
	else if (win(2))
	{
		//white wins
		std::cout << "White Wins!" << std::endl;
		gameEnd = 1;
	}
	else if (boardfull())
	{
		//draw
		std::cout << "This game ended in a draw" << std::endl;
		gameEnd = 1;
	}
	return gameEnd;
}

void game::setBoard(std::string addr, int color)
{
	int r, i;
	i = addr[0] - 'A' ;
	r = addr[1] - '1';

	b->at(r).at(i) = color;
}

int game::sanitycheck_input(std::string addr)
{
	if (addr.size() < 2) return 0;
	if (addr[0] >= 'A' && addr[0] <= 'C' && addr[1] >= '1' && addr[1] <= '3') 
	{
		int t1 = addr[0] - 'A';
		int t2 = addr[1] - '1';
		if (b->at(t2).at(t1) == 0) return 1;
	}
	return 0;
}