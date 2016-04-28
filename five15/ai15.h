#pragma once
#include "board.h"

class ai15
{
private:

public:
	ai15();
	~ai15();

	int avalue3_w(board*);

	int choice(board*, int);
	int vsimplechoice(board*, int);

};
