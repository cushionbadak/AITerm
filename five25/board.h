#pragma once
#include <iostream>
#include <vector>
#define SIZE 5
#define WINLEN 5

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
	
	

	
};