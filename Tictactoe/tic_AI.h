#pragma once
#include <vector>
#include <iostream>
#include <string>

#define SIZE 3
#define WINLEN 3

typedef std::vector<std::vector <int> > brd;

class tic_AI
{
private:

public:
	tic_AI();
	~tic_AI();
	std::string bestChoice(brd, int);
	std::string addrToStr(int, int);
	std::string simpleChoice(brd);
	int win(brd, int);
	void setBrd(brd*, int, int, int);
};