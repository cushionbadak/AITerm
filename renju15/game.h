#pragma once
#include "board.h"
#include "lines.h"
#include "ai.h"

class game {
private:

public:
	game();
	~game();

	lines *bef_l;
	lines *cur_l;
	board *bef_b;
	board *cur_b;
	ai *aiai;

	int game_start(void);
};