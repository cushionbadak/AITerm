#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#define SIZE 5
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
	//int win (int color)
	int win(int);
	//int threethree (int color)
	int threethree(int);
	//int openfour(int color) __ TODO
	int openfour(int);
	//int fourthree (int color) __ TODO
	int fourthree(int);
	
	
	int isFull();
	//void setBoard(int addr, int color)
	void setBoard(int, int);
	void printBoard();
	int str2Addr(std::string);
	void headtailprint();
	void firstprint();
	void lastprint();
	void bodyprint();
	std::string mmm(int, int);
	std::string addr2Str(int);
};