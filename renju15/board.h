#pragma once
#include <vector>

// mandatory : BLACK and WHITE must not be 0
#define BRDSIZE 15
#define EMPTY 0
#define BLACK 1
#define WHITE 2

typedef std::vector<int> bb;

class board {
private:

public:
	board();
	~board();

	//IMPORTANT
	//brd->at(0) is at 'leftup', brd->at(1) is located at right of brd->at(0)
	bb *brd;

	int color_sanity(int color);
	int addr_sanity(int addr);

	int set_board(int addr, int color);
	int set_board_safe(int addr, int color);

	int is_board_full();

};