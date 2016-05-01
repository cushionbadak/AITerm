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
	int is_d3_new_method_sub(board *brda, std::pair<int, int> center, int color, int f_change, int s_change);
	int is_d3_wrap(board *brda, int addr, int color);

	int pick(board *bbb);
	int simple_pick(bb *b);

	int black_ai_value_when_applied(board *brda, int addr, int color);
	int black_ai_board_value(board *brda);
	int black_ai_lines_value(lines *cur_l);
	int black_ai_value_factor(int size);

	int black_ai_shallow_search(board *brda);
	std::vector<int> available_addrs(board *brda, int color);
};