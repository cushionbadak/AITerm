#pragma once
#include <vector>
#include <iostream>
#include <string>

#define SIZE 3
#define WINLEN 3

typedef std::vector<int> row;
typedef std::vector<row> board;

class game
{

private:
	board *b;

public:
	game();
	~game();

	void test1(void);
	void start(void);
	
	void printBoard(void);
	std::string printhelper(int);
	std::string getColorString(int i);
	
	int win(int);
	int boardfull(void);
	int isGameEnd(void);


	void setBoard(std::string, int);
	int sanitycheck_input(std::string);
};