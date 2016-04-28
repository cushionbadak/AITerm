#pragma once
#include "board.h"
#include "lines.h"

class game {
private:

public:
	game();
	~game();

	lines *bef_l;
	lines *cur_l;
	board *bef_b;
	board *cur_b;

	int game_start(void);
};