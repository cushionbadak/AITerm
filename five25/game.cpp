#include "game.h"

game::game()
{
	AI = new ai25();
	brd = new board();
}

game::~game()
{
	AI->~ai25();
	brd->~board();
}

void game::start()
{
	std::string input1;

	std::cout << std::endl << "Start renju" << std::endl << std::endl;
	brd->setBoard(AI->choice(brd, BLACK), BLACK);
	while (1)
	{
		//if black wins
		if (brd->win(BLACK))
		{
			winprint(BLACK);
			break;
		}
		//or board full
		if (brd->isFull())
		{
			drawprint();
			break;
		}
		
		//white turn
			//board print
		brd->printBoard();
		while (1) {
			//require input
			std::cout << std::endl << "White turn, Reqruie Your Input : ";
			std::cin >> input1;
			//input sanity check
			if (inputSanityCheck(input1))
			{
				break;
			}
			else
			{
				std::cout << std::endl << "It's inappropriate input." << std::endl;
			}
		}
		//setBoard
		brd->setBoard(brd->str2Addr(input1), WHITE);

		//if white wins
		if (brd->win(WHITE))
		{
			winprint(WHITE);
			break;
		}
		//or board full
		if (brd->isFull())
		{
			drawprint();
			break;
		}

		//black turn
			//require AI
		std::cout << std::endl << "AI thinking..." << std::endl;
		brd->setBoard(AI->choice(brd, BLACK), BLACK);
	}

}

void game::winprint(int color)
{
	std::cout << std::endl;
	//print board
	brd->printBoard();
	//black wins
	if (color == BLACK)
	{
		std::cout << "¡Û¡Û¡Û¡Û" << std::endl << "BLACK WIN!" << std::endl << "¡Û¡Û¡Û¡Û" << std::endl;
	}
	//white wins
	else if (color == WHITE)
	{
		std::cout << "¡Ü¡Ü¡Ü¡Ü" << std::endl << "WHITE WIN!" << std::endl << "¡Ü¡Ü¡Ü¡Ü" << std::endl;
	}
	//otherwise
	else
	{
		std::cout << "¡Û¡Û¡Ü¡Ü" << std::endl << "SOMEONE WIN!" << std::endl << "¡Ü¡Ü££££" << std::endl;
	}
}
void game::drawprint()
{
	brd->printBoard();
	std::cout << "££££££££" << std::endl << "DRAW!" << std::endl << "££££££££" << std::endl;
}
int game::inputSanityCheck(std::string input)
{
	//output 0 means inappropriate input
	//check length
	if (SIZE < 10)
	{
		if (input.length() != 2) return 0;
		//first letter
		else if (input[0] - 'A' < 0 || input[0] - 'A' >= SIZE) return 0;
		//second letter
		else if (input[1] - '0' <= 0 || input[1] - '0' > SIZE) return 0;
		//all is well
		else
		{
			return 1;
		}
	}
	else if (SIZE < 20)
	{
		if (input.length() > 3) return 0;
		else if (input[1] == '1')
		{
			//first letter
			if (input[0] - 'A' < 0 || input[0] - 'A' >= SIZE) return 0;
			//third letter
			else if (input[2] && (input[2] - '0' <= 0 || input[2] - '0' + 10 > SIZE)) return 0;
			//all is well
			else
			{
				return 1;
			}
		}
		else
		{
			//first letter
			if (input[0] - 'A' < 0 || input[0] - 'A' >= SIZE) return 0;
			//second letter
			else if (input[1] - '0' <= 0 || input[1] - '0' >= 10) return 0;
		}
	}
	else
	{
		//TODO_ SIZE over 19
		std::cout << "WARNING : game::inputSanityCheck are not completed" << std::endl;
		return 1;
	}
}