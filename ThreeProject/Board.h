#pragma once
#include <vector>
#include <tuple>
#include <utility>
#include <iostream>


typedef std::vector <std::vector <int> > vector2_int;
typedef std::tuple<int, int, int, int, int, int, int, int> _eight_int_tuple;
typedef std::tuple<int, int, int, int, int, int, int, int, int, std::pair<int, int> > _ten_tuple;


class Board
{
public:
	/*
		Board(int, int) 에서 winlength = 3 이다.
		Board(int, int, int) 에서 winlength 는 마지막 매개변수이다.
	*/
	Board(int, int);
	Board(int, int, int);
	virtual ~Board();

	/*
		setBoardplate_fillzero
		해당 인수를 받아 같은 자리의 내용을 바꾸고, 만약 인수에서 정의되지 않은 부분은 0으로 채운다.
	*/
	void setBoardplate_fillzero(Board);
	void setBoardplate_fillzero(vector2_int);

	/*
		setBoardplate(int _height, int_width, int num) 
		boardplate[_height][_width] 의 값을 num으로 바꾼다.
	*/
	void setBoardplate(int, int, int);
	int getBoardplate(int, int);
	vector2_int getBoardplate();
	int getHeight();
	int getWidth();

	/*
		inHeight, inWidth
		매개변수가 0과 height-1 (또는 width-1) 값 안에 있는지 확인한다 
	*/
	int inHeight(int);
	int inWidth(int);

	/*
		SearchWinPosition_point(int _height, int _width, int num)
		boardplate[_height][_width] 를 8방향의 중심으로 한 수만에 winlength가 만들어지는지 찾는다.
		만들어진다면 그 한 수의 위치를 반환한다.
		없을 경우 (-1, -1)을 반환한다.
	*/
	std::pair<int, int> searchWinPosition_point(int, int, int);
	_ten_tuple search_sub(_eight_int_tuple);

	/*
		유닛 테스트용 메소드이다.
	*/
	void test1();

	int getWinlength();

private:
	int height, width;
	int winlength;
	vector2_int *boardplate;


};
