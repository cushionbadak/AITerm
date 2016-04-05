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
	//search not start from (0, 0)
	//it looks like backslash search on terminal output
	for (iter1 = 0; iter1 < SIZE - WINLEN + 1; iter1++)
	{
		for (iter2 = WINLEN - 1; iter2 < SIZE; iter2++)
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
	//search start from (0, 0)
	//it looks like slash search on terminal output
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
int board::isEmpty()
{
	int iter1;
	for (iter1 = 0; iter1 < SIZE*SIZE; iter1++)
	{
		if (b->at(iter1) != EMPTY) return 0;
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
	else
	{
		std::cout << "Warning : setBoard Fail" << std::endl;
	}
}

void board::printBoard()
{
	std::cout << std::endl << std::endl;
	//head
	headtailprint();
	//first
	firstprint();
	//body
	bodyprint();
	//last
	lastprint();
	//tail
	headtailprint();
	std::cout << std::endl << " Black : " <<  "¡Û" << "  , White : " << "¡Ü" << std::endl << std::endl;
}
int board::str2Addr(std::string input)
{
	if (SIZE < 10)
	{
		return (input[1] - '1') * SIZE + (input[0] - 'A');
	}
	else if (SIZE < 20)
	{
		if (input[1] == '1')
		{
			if (input[2])
			{
				return (10 + input[2] - '1') * SIZE + (input[0] - 'A');
			}
			else
			{
				return (input[1] - '1') * SIZE + (input[0] - 'A');
			}
		}
		else
		{
			return (input[1] - '1') * SIZE + (input[0] - 'A');
		}
	}
	else
	{
		//TODO
		std::cout << "WARNING : board::str2Addr are not completed." << std::endl;
		return (input[1] - '1') * SIZE + (input[0] - 'A');
	}
}

void board::headtailprint()
{
	int iter1;
	std::cout << std::setw(5) << " ";
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
	std::cout << std::setw(3) << std::to_string(SIZE) << " " << mmm(b->at(SIZE * (SIZE - 1)), 1);
	for (iter1 = 1; iter1 < SIZE - 1; iter1++)
	{
		temp.append(mmm(b->at(SIZE*(SIZE - 1) + iter1), 5));
	}
	std::cout << temp << mmm(b->at(SIZE * SIZE - 1), 2) << std::to_string(SIZE) << std::endl;
}
void board::lastprint()
{
	//only works well when (SIZE > 1)
	int iter1;
	std::string temp;
	std::cout << std::setw(3) << "1" << " " << mmm(b->at(0), 3);
	for (iter1 = 1; iter1 < SIZE - 1; iter1++)
	{
		temp.append(mmm(b->at(iter1), 6));
	}
	std::cout << temp << mmm(b->at(SIZE - 1), 4) << "1" << std::endl;
}
void board::bodyprint()
{
	int iter1, iter2;
	std::string temp;
	//each row iteration
	for (iter1 = SIZE - 2; iter1 > 0; iter1--)
	{
		temp.clear();
		//number print
		std::cout << std::setw(3) << std::to_string(iter1 + 1) << " ";
		//first element
		temp.append(mmm(b->at(iter1 * SIZE), 7));
		//each column iteration
		for (iter2 = 1; iter2 < SIZE - 1; iter2++)
		{
			temp.append(mmm(b->at(iter1*SIZE + iter2), 0));
		}
		//last element
		temp.append(mmm(b->at(iter1*SIZE + (SIZE - 1)), 8));
		//number print
		std::cout << temp << std::to_string(iter1 + 1) << std::endl;
	}
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

std::string board::addr2Str(int addr)
{
	int row, alphabet;
	std::string str;

	row = (addr / SIZE);
	alphabet = (addr % SIZE);


	str.append(std::to_string(row));
	str.append(std::to_string(alphabet));
	return str;
}


std::tuple<int, int> board::addr2Tu(int addr)
{
	int a, b;
	a = addr / SIZE;
	b = addr % SIZE;
	std::tuple<int, int> r = std::make_tuple(a, b);
	return r;
}

int board::tu2Addr(std::tuple<int, int> tu)
{
	return std::get<0>(tu)*SIZE + std::get<1>(tu);
}

int board::otherColor(int color)
{
	if (color == BLACK)
	{
		return WHITE;
	}
	else if (color == WHITE)
	{
		return BLACK;
	}
	else
	{
		return -1;
	}
}