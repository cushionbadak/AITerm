#pragma once
#include <vector>
#include <iostream>
#include <string>

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
	int str2addr(std::string str);
	int reverse_color(int color);

	int set_board(int addr, int color);
	int set_board_safe(int addr, int color);
	int get_board_safe(int addr);

	int is_board_full();

	int board_print();
	int board_print_base(int n, std::string firststr, std::string bodystr, std::string laststr);
	int board_print_up();
	int board_print_down();
	int board_print_body(int n);
	std::string bw_string(int color);
};