#pragma once
#include "board.h"

class ai25
{
private:

public:
	ai25();
	~ai25();
	int choice(board*, int);
	int vsimplechoice(board*, int);
	int achoice(board*, int);

	std::vector<std::tuple<int, int>> getHvalue(board*);
	std::vector<std::tuple<int, int>> getVvalue(board*);
	std::tuple<int, int> getSvalue(board*);
	std::tuple<int, int> getBvalue(board*);

	std::tuple<int, int> calvalue(int, int);
	std::vector<std::tuple<int, int>> valueSort_b(std::vector<std::tuple<int, int>>);
	std::vector<std::tuple<int, int>> valueSort_w(std::vector<std::tuple<int, int>>);

};