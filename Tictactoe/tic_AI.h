#pragma once
#include <vector>
#include <iostream>
#include <string>


#define SIZE 3
#define WINLEN 3

class tic_AI
{
private:

public:
	tic_AI();
	~tic_AI();
	std::string bestChoice(std::vector<std::vector<int> >, int);
	std::string addrToStr(int, int);
	std::string simpleChoice(std::vector<std::vector<int> >);
};