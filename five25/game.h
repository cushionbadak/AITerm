#pragma once
#include "ai25.h"

class game
{
private:

public:
	ai25 *AI;
	board *brd;

	game();
	~game();
	void start();
	void winprint(int);
	void drawprint();
	int inputSanityCheck(std::string);

};