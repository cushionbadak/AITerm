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
		Board(int, int) ���� winlength = 3 �̴�.
		Board(int, int, int) ���� winlength �� ������ �Ű������̴�.
	*/
	Board(int, int);
	Board(int, int, int);
	virtual ~Board();

	/*
		setBoardplate_fillzero
		�ش� �μ��� �޾� ���� �ڸ��� ������ �ٲٰ�, ���� �μ����� ���ǵ��� ���� �κ��� 0���� ä���.
	*/
	void setBoardplate_fillzero(Board);
	void setBoardplate_fillzero(vector2_int);

	/*
		setBoardplate(int _height, int_width, int num) 
		boardplate[_height][_width] �� ���� num���� �ٲ۴�.
	*/
	void setBoardplate(int, int, int);
	int getBoardplate(int, int);
	vector2_int getBoardplate();
	int getHeight();
	int getWidth();

	/*
		inHeight, inWidth
		�Ű������� 0�� height-1 (�Ǵ� width-1) �� �ȿ� �ִ��� Ȯ���Ѵ� 
	*/
	int inHeight(int);
	int inWidth(int);

	/*
		SearchWinPosition_point(int _height, int _width, int num)
		boardplate[_height][_width] �� 8������ �߽����� �� ������ winlength�� ����������� ã�´�.
		��������ٸ� �� �� ���� ��ġ�� ��ȯ�Ѵ�.
		���� ��� (-1, -1)�� ��ȯ�Ѵ�.
	*/
	std::pair<int, int> searchWinPosition_point(int, int, int);
	_ten_tuple search_sub(_eight_int_tuple);

	/*
		���� �׽�Ʈ�� �޼ҵ��̴�.
	*/
	void test1();

	int getWinlength();

private:
	int height, width;
	int winlength;
	vector2_int *boardplate;


};
