#pragma once
#include "board.h"
#include "lines.h"

class ai {
private:

public:
	ai();
	~ai();

	int is_d3_lines(lines *bef_l, lines *cur_l, int color);
	int is_d3_future(board *brda, int addr, int color);
	int is_d3_new_method(board *brda, int addr, int color);
	int is_d3_wrap(board *brda, int addr, int color);

	int pick(board *bbb);
	int simple_pick(bb *b);
};