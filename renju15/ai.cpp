#include "ai.h"

ai::ai()
{

}

ai::~ai()
{

}

int ai::is_d3_lines(lines *bef_l, lines *cur_l, int color)
{
	// if double-3 appears, return 1
	// else return 0
	if (bef_l->count(color, 3) + 4 <= cur_l->count(color, 3)) return 1;
	return 0;
}

int ai::is_d3_future(board *brda, int addr, int color)
{
	// if double-3 appears, return 1
	// else return 0
	int result = 0;
	int status = 0;
	lines *before = new lines();
	lines *after = new lines();
	
	before->full_update(brda->brd);
	status = brda->set_board_safe(addr, color);
	if (status != 0) return 0;
	after->full_update(brda->brd);
	result = is_d3_lines(before, after, color);

	brda->set_board(addr, EMPTY);
	before->~lines();
	after->~lines();
	return result;
}

int ai::is_d3_new_method(board *brda, int addr, int color)
{
	// if double - 3, return 1
	// else, return 0.
	//////
	// 0 ~ 10, addr is center
	// oooooXooooo : 4 times
	// 2 pointers -> one moves left, one moves right
	// if it met 2 blanks, it stops and back once
	// only length 5 and 3 'color' allowed, and XoXoX not allowed
	// if pointer met other color or wall(-1), move pointer. only second blank stops it.
	// length 5 and 3 'color' will solves other color and wall confusing problem 
	// other-> if other color in length5, return 0
	return 0;
}

int ai::is_d3_wrap(board *brda, int addr, int color)
{
	return is_d3_future(brda, addr, color);
}

int ai::pick(board *bbb)
{
	//wrapper
	return simple_pick(bbb->brd);
}

int ai::simple_pick(bb *b)
{
	// return first empty address
	// if board is full, return -1;
	int i;
	for (i = 0; i < (int)(b->size()); i++) if (b->at(i) == EMPTY) return i;
	return -1;
}