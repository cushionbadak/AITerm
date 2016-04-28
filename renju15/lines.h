#pragma once
#include <vector>
#include "board.h"

#define LINESIZE 5
#define UNITSIZE (BRDSIZE - LINESIZE + 1)	//11

class lines {
private:

public:
	lines();
	~lines();

	std::vector<int> *horlines;	//horizontal lines
	std::vector<int> *verlines;	//vertical lines
	std::vector<int> *sshlines;	//slash lines
	std::vector<int> *bshlines;	//backslash lines

	int hor_start(int n);
	int ver_start(int n);
	int ssh_start(int n);
	int bsh_start(int n);

	int setline_base(int n, bb *b, int iter_v);
	int hor_setline(int n, bb *b);
	int ver_setline(int n, bb *b);
	int ssh_setline(int n, bb *b);
	int bsh_setline(int n, bb *b);

	int xor_bw(int b, int w);
	int full_update(bb *b);

	int count(int color, int size);
	int countover(int color, int size);
	int countunder(int color, int size);

	int black_win();
	int white_win();
	int csv(int color, int size);	//it returns value
};