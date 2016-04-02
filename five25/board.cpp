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

//int threethree (int color) __ TODO
int board::threethree(int color)
{
	return 0;
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


int board::isFull()
{
	//if board is full, return 1
	int iter1;
	for (iter1 = 0; iter1 < SIZE*SIZE; iter1++)
	{
		if (b->at(iter1) == EMPTY) return 0;
	}
	return 1;
}
//void setBoard(int addr, int color)
void board::setBoard(int addr, int color)
{
	if (addr >= 0 && addr < SIZE*SIZE)
	{
		b->at(addr) = color;
	}
}

void board::printBoard()
{
	//TODODODODO
	std::cout << std::endl << std::endl;
	//head
	headtailprint();
	//first
	firstprint();
	//body
	//last
	lastprint();
	//tail
	headtailprint();
	std::cout << std::endl << " Black : " << bl << "  , White : " << wh << std::endl << std::endl;
	
}
int board::str2Addr(std::string input)
{
	return (input[1] - '0') * SIZE + (input[0] - 'A');
}

void board::headtailprint()
{
	int iter1;
	std::cout << "  ";
	for (iter1 = 0; iter1 < SIZE; iter1++)
	{
		std::cout << (char)(iter1 + 'A') << " ";
	}
	std::cout << std::endl;
}

void board::firstprint()
{
	//only works well when (SIZE > 1)
	int iter1;
	std::string temp;
	temp.clear();
	std::cout << (char)iter1 << " " << mmm(b->at(SIZE * (SIZE - 1)), 1);
	for (iter1 = 1; iter1 < SIZE - 1; iter1++)
	{
		temp.append(mmm(b->at(SIZE*(SIZE - 1) + iter1), 5));
	}
	std::cout << temp << mmm(b->at(SIZE * SIZE - 1), 2) << " " << (char)iter1 << std::endl;
}
void board::lastprint()
{
	//only works well when (SIZE > 1)
	int iter1;
	std::string temp;
	temp.clear();
	std::cout << (char)iter1 << " " << mmm(b->at(0), 3);
	for (iter1 = 1; iter1 < SIZE - 1; iter1++)
	{
		temp.append(mmm(b->at(iter1), 6));
	}
	std::cout << temp << mmm(b->at(SIZE - 1), 4) << " " << (char)iter1 << std::endl;
}
std::string board::mmm(int color, int deflt)
{
	if(color == BLACK) return "¡Û";
	else if (color == WHITE) return "¡Ü";
	else if (color == EMPTY)
	{
		switch (deflt)
		{
		case 0: return "¦«";
		case 1: return "¦£";
		case 2: return "¦¤";
		case 3: return "¦¦";
		case 4: return "¦¥";
		case 5: return "¦¨";
		case 6: return "¦ª";
		case 7: return "¦§";
		case 8: return "¦©";
		default: return "¡Ú";
		}
	}
	else
	{
		return "£À";
	}
}