#pragma once
#include "Board.h"

Board::Board(int _height, int _width)
{
	winlength = 3;
	if (_height < 1) 
	{
		throw "Board Constructor : inappropriate input : _height";
	}
	else if (_width < 1)
	{
		throw "Board Construtor : inappropriate input : _width";
	}
	else
	{
		height = _height;
		width = _width;
		boardplate = new vector2_int();
		for (int i = 0; i < height; i++)
		{
			std::vector<int> *temp = new std::vector<int>();
			for (int j = 0; j < width; j++)
			{
				temp->push_back(0);
			}
			boardplate->push_back(*temp);
			delete temp;
		}
	}
}
Board::Board(int _height, int _width, int _winlength)
{
	winlength = _winlength;
	if (_height < 1)
	{
		throw "Board Constructor : inappropriate input : _height";
	}
	else if (_width < 1)
	{
		throw "Board Construtor : inappropriate input : _width";
	}
	else
	{
		height = _height;
		width = _width;
		boardplate = new vector2_int();
		for (int i = 0; i < height; i++)
		{
			std::vector<int> *temp = new std::vector<int>();
			for (int j = 0; j < width; j++)
			{
				temp->push_back(0);
			}
			boardplate->push_back(*temp);
			delete temp;
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < height; i++) 
	{
		(boardplate->back().~vector());
	}
	boardplate->~vector();
	delete boardplate;
}

void Board::setBoardplate_fillzero(vector2_int brd)
{
	for (int i = 0; i < height; i++)
	{
		if ((int)brd.size() - 1 < i)
		{
			for (int j = 0; j < width; j++)
			{
				boardplate->at(i).at(j) = 0;
			}
		}
		else
		{
			for (int j = 0; j < width; j++)
			{
				if ((int)brd.at(i).size() - 1 < j)
				{
					boardplate->at(i).at(j) = 0;
				}
				else
				{
					if (brd.at(i).at(j) == -1) boardplate->at(i).at(j) = 0;
					else boardplate->at(i).at(j) = brd.at(i).at(j);
				}
			}
		}
	}
}


void Board::setBoardplate_fillzero(Board b)
{
	setBoardplate_fillzero(b.getBoardplate());
}

void Board::setBoardplate(int _height, int _width, int num)
{
	if (inHeight(_height) && inWidth(_width))
	{
		boardplate->at(_height).at(_width) = num;
	}
}

int Board::getBoardplate(int _height, int _width)
{
	if (inHeight(_height) && inWidth(_width))
	{
		return boardplate->at(_height).at(_width);
	}
	else return -1;
}

vector2_int Board::getBoardplate()
{
	return *boardplate;
}

int Board::getHeight()
{
	return height;
}

int Board::getWidth()
{
	return width;
}

int Board::inHeight(int num)
{
	return (num >= 0 && num < height);
}

int Board::inWidth(int num)
{
	return (num >= 0 && num < width);
}


void Board::test1()
{
	std::cout << "hello world" << " " << boardplate->at(2).at(2) << std::endl;
	setBoardplate(1, 2, 1);
	setBoardplate(2, 2, 1);
	std::cout << "searchWinPosition_point : " << searchWinPosition_point(2, 2, 1).first << searchWinPosition_point(2, 2, 1).second << std::endl;
	std::cout << "1, 2" << " " << boardplate->at(1).at(2) << std::endl;
	std::cout << "getBoardplate" << " " << getBoardplate(1, 2) << std::endl;
	std::cout << "winlength : " << winlength << std::endl;
}

std::pair<int, int> Board::searchWinPosition_point(int _height, int _width, int num)
{
	std::pair<int, int> default = std::pair<int, int>(-1, -1);
	if (!(inHeight(_height) && inWidth(_width))) return default;	//inappropriate _height or _width


	/*
		temph tempw: 위치
		rest1 rest2 : 개수세기
		status 0 : "blocked"
		status 1 : "blank"
		status 2 : "continue"
		resulth, resultw : 반환값
		ttt : boardplate 저장
	*/
	int temph, tempw, rest1, rest2;
	int status;
	int resulth, resultw;
	int ttt;
	_eight_int_tuple a;
	_ten_tuple b;

	// horizontal search
	temph = _height; tempw = 0; rest1 = 0; rest2 = 0;
	status = 0;
	resulth = -1; resultw = -1;
	ttt = 0;
	for (tempw = 0; tempw < width; tempw++)
	{
		a = _eight_int_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num);
		b = search_sub(a);
		if (std::get<8>(b)) return std::get<9>(b);
		else {
			temph = std::get<0>(b);
			tempw = std::get<1>(b);
			rest1 = std::get<2>(b);
			rest2 = std::get<3>(b);
			status = std::get<4>(b);
			resulth = std::get<5>(b);
			resultw = std::get<6>(b);
		}
	}

	// vertical search
	temph = 0; tempw = _width; rest1 = 0; rest2 = 0;
	status = 0;
	resulth = -1; resultw = -1;
	ttt = 0;
	for (temph = 0; temph < height; temph++)
	{
		a = _eight_int_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num);
		b = search_sub(a);
		if (std::get<8>(b)) return std::get<9>(b);
		else {
			temph = std::get<0>(b);
			tempw = std::get<1>(b);
			rest1 = std::get<2>(b);
			rest2 = std::get<3>(b);
			status = std::get<4>(b);
			resulth = std::get<5>(b);
			resultw = std::get<6>(b);
		}
	}

	// backslash search
	temph = _height; tempw = _width; rest1 = 0; rest2 = 0;
	status = 0;
	resulth = -1; resultw = -1;
	ttt = 0;

	while(tempw > 0 && temph > 0)
	{
		tempw--;
		temph--;
	}

	for (tempw; tempw < width; tempw++)
	{
		if (!(temph > height - 1)) break;

		a = _eight_int_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num);
		b = search_sub(a);
		if (std::get<8>(b)) return std::get<9>(b);
		else {
			temph = std::get<0>(b);
			tempw = std::get<1>(b);
			rest1 = std::get<2>(b);
			rest2 = std::get<3>(b);
			status = std::get<4>(b);
			resulth = std::get<5>(b);
			resultw = std::get<6>(b);
		}

		temph++;
	}

	// slash search
	temph = _height; tempw = _width; rest1 = 0; rest2 = 0;
	status = 0;
	resulth = -1; resultw = -1;
	ttt = 0;

	while (temph > 0 && tempw < width - 1)
	{
		temph--;
		tempw++;
	}

	for (temph; temph < height; temph++)
	{
		if (tempw < 0) break;

		a = _eight_int_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num);
		b = search_sub(a);
		if (std::get<8>(b)) return std::get<9>(b);
		else {
			temph = std::get<0>(b);
			tempw = std::get<1>(b);
			rest1 = std::get<2>(b);
			rest2 = std::get<3>(b);
			status = std::get<4>(b);
			resulth = std::get<5>(b);
			resultw = std::get<6>(b);
		}

		tempw--;
	}

	return default;
}

/*
temph tempw: 위치
rest1 rest2 : 개수세기
status 0 : "blocked"
status 1 : "blank"
status 2 : "continue"
resulth, resultw : 반환값
ttt : boardplate 저장
*/
_ten_tuple Board::search_sub(_eight_int_tuple a)
{
	/*
	temph tempw: 위치
	rest1 rest2 : 개수세기
	status 0 : "blocked"
	status 1 : "blank"
	status 2 : "continue"
	resulth, resultw : 반환값
	num : board 내의 색
	ttt : boardplate 저장
	*/
	int temph, tempw, rest1, rest2;
	int status;
	int resulth, resultw;
	int num;
	int ttt;

	//input
	temph = std::get<0>(a);
	tempw = std::get<1>(a);
	rest1 = std::get<2>(a);
	rest2 = std::get<3>(a);
	status = std::get<4>(a);
	resulth = std::get<5>(a);
	resultw = std::get<6>(a);
	num = std::get<7>(a);


	ttt = boardplate->at(temph).at(tempw);
	//status 0 : blocked
	if (status == 0)
	{
		//blank
		if (ttt == 0)
		{
			rest1 = 0; rest2 = 0;
			status = 1;
			resulth = temph; resultw = tempw;
		}
		//continue
		else if (ttt == num)
		{
			rest1++; rest2 = 0;
			status = 2;
			resulth = -1; resultw = -1;
		}
		//blocked
		else
		{
			rest1 = 0; rest2 = 0;
			status = 0;
			resulth = -1; resultw = -1;
		}
	}
	//status 1 : blank
	else if (status == 1)
	{
		//blank
		if (ttt == 0)
		{
			if (rest1 + rest2 >= winlength - 1) 
				return _ten_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num, 1, std::pair<int, int>(resulth, resultw));
			rest1 = rest2; rest2 = 0;
			status = 1;
			resulth = temph; resultw = tempw;
		}
		//continue
		else if (ttt == num)
		{
			if (rest1 + rest2 >= winlength - 1)
				return _ten_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num, 1, std::pair<int, int>(resulth, resultw));
			rest1 = rest1; rest2++;
			status = 1;
			resulth = resulth; resultw = resultw;
		}
		//blocked
		else
		{
			if (rest1 + rest2 >= winlength - 1) 
				return _ten_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num, 1, std::pair<int, int>(resulth, resultw));
			rest1 = 0; rest2 = 0;
			status = 0;
			resulth = -1; resultw = -1;
		}
	}
	//status 2 : continue
	else if (status == 2)
	{
		//blank
		if (ttt == 0)
		{
			if (rest1 >= winlength - 1) 
				return _ten_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num, 1, std::pair<int, int>(temph, tempw));
			rest1 = rest1; rest2 = 0;
			status = 1;
			resulth = temph; resultw = tempw;
		}
		//continue
		else if (ttt == num)
		{
			rest1++; rest2 = 0;
			status = 2;
			resulth = resulth; resultw = resultw;
		}
		//blocked
		else
		{
			rest1 = 0; rest2 = 0;
			status = 0;
			resulth = -1; resultw = -1;
		}
	}
	return _ten_tuple(temph, tempw, rest1, rest2, status, resulth, resultw, num, 0, std::pair<int, int>(-1, -1));
}

int Board::getWinlength()
{
	return winlength;
}