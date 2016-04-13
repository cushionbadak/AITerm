#pragma once
#include "ai15.h"

class game
{
private:

public:
	ai15 *AI;
	board *brd;

	game();
	~game();
	void start();
	void winprint(int);
	void drawprint();
	int inputSanityCheck(std::string);

};