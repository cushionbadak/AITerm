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

	int avalue3_b(board*);
	int avalue3_w(board*);
	std::vector<std::tuple<int, int>> acheck(board*);

	std::vector<std::tuple<int, int>> getHvalue(board*);
	std::vector<std::tuple<int, int>> getVvalue(board*);
	std::tuple<int, int> getSvalue(board*);
	std::tuple<int, int> getBvalue(board*);

	std::tuple<int, int> calvalue(int, int);
	std::vector<std::tuple<int, int>> valueSort_b(std::vector<std::tuple<int, int>>);
	std::vector<std::tuple<int, int>> valueSort_w(std::vector<std::tuple<int, int>>);

	std::vector<int> vSort_b(std::vector<std::tuple<int, int>>);
	std::vector<int> vSort_w(std::vector<std::tuple<int, int>>);
	int getMax_b(std::vector<std::tuple<int, int, int>>);
	int getMax_w(std::vector<std::tuple<int, int, int>>);
	int getnummax_b(std::vector<std::tuple<int, int, int>>, int);
	int getnummax_w(std::vector<std::tuple<int, int, int>>, int);

	int get1addr4(int, board*);
};