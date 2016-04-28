#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <tuple>

#define SIZE 15
#define WINLEN 5

#define EMPTY 0
#define BLACK 1
#define WHITE 2

class board
{
private:

public:
	//const, dest
	board();
	~board();

	//vector<int>, size SIZE * SIZE
	std::vector<int> *b;
	int win(int);
	int threethree(int);
	int openfour(int);
	int fourthree(int);


	int isFull();
	int isEmpty();
	int isPointEmpty(int);

	//void setBoard(int addr, int color)
	void setBoard(int, int);
	int str2Addr(std::string);
	std::string addr2Str(int);

	void printBoard();
	void headtailprint();
	void firstprint();
	void lastprint();
	void bodyprint();
	std::string mmm(int, int);

	std::tuple<int, int> addr2Tu(int);
	int tu2Addr(std::tuple<int, int>);

	int otherColor(int);
};