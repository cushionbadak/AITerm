#pragma once
#include "board.h"
#include "lines.h"

#define W_WL 2.8
#define W_BL 3.8
#define B_WL 3.2
#define B_BL 2.8
// In common sense, W_WL < W_BL and B_WL > B_BL is good
// -1000000 and 10000000 used instead of infinity value (when five stones in one line),
// so it is recommended to use float value under 20.

// experiment result (W_WL, W_BL, B_WL, B_BL)
// (2.0, 3.0, 4.0, 3.0) -> DRAW
// (5.0, 7.0, 4.0, 3.0) -> WHITE WIN
// (5.0, 7.0, 7.0, 5.0) -> WHITE WIN
// (5.0, 7.0, 6.0, 5.0) -> WHITE WIN
// (5.0, 7.0, 3.0, 2.0) -> DRAW
// (5.0, 7.0, 3.0, 2.7) -> BLACK WIN
// (5.0, 8.0, 3.0, 2.7) -> DRAW
// (5.0, 8.0, 3.0, 3.1) -> WHITE WIN

// (2.8, 3.8, 3.0, 2.8) -> DRAW
// (2.8, 3.8, 3.1, 2.8) -> DRAW
// (2.8, 3.8, 3.8, 2.8) -> WHITE WIN
// (2.8, 3.8, 3.3, 2.8) -> BLACK WIN

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

	int pick(board *bbb, int color);
	int simple_pick(bb *b);

	int value_when_applied(board *brda, int addr, int color);
	int board_value(board *brda, int color);
	int lines_value(lines *cur_l, int color);
	int black_ai_value_factor(int size);
	int white_ai_value_factor(int size);

	int ai_shallow_search(board *brda, int color);
	std::vector<int> available_addrs(board *brda, int color);
};