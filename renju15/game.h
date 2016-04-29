#pragma once
#include "board.h"
#include "lines.h"
#include "ai.h"

class game {
private:

public:
	game();
	~game();

	//lines *bef_l;
	lines *cur_l;
	//board *bef_b;
	board *cur_b;
	ai *aiai;

	// black_play, white_play : 0 is AI, 1 is user
	int black_play;
	int white_play;

	int game_start(void);
	int turn(int color);
	int turn_start(int color, int status);

	int color_and_play(int color);
};