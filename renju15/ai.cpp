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

	if (brda->set_board_safe(addr, color)) return 0;
	// board changed.

	std::pair<int, int> center = brda->addr2pair(addr);
	int counter = 0;
	// horizontal, vertical, slash, backslash
	counter += is_d3_new_method_sub(brda, center, color, 1, 0);
	counter += is_d3_new_method_sub(brda, center, color, 0, 1);
	counter += is_d3_new_method_sub(brda, center, color, 1, 1);
	counter += is_d3_new_method_sub(brda, center, color, 1, -1);

	brda->set_board(addr, EMPTY);
	// board returned to original board.
	if (counter > 1) return 1;
	else return 0;
}

int ai::is_d3_new_method_sub(board *brda, std::pair<int, int> center, int color, int f_change, int s_change)
{
	// check 3 for only two direction from center.
	// if 3 -> return 1, else, return 0.
	// center's color must be equal to argument 'color'
	int i, temp;
	int t1, t2, t3, t4, t5;
	int f = center.first;
	int s = center.second;
	int count_empty_l = 0;
	int count_empty_r = 0;
	int count_color = 0;
	int count_other_color = 0;
	int pointer_l = 1;
	int pointer_r = 0;
	int reverse_color = brda->reverse_color(color);
	for (i = 0; i < 6; i++)
	{
		// right move
		pointer_r = i;
		temp = brda->get_board_from_pair(std::pair<int, int>(f + f_change * i, s + s_change * i));
		if (temp == EMPTY)
		{
			if (count_empty_r == 1) { break; }
			else { count_empty_r++; continue; }
		}
		else if (temp == color) { count_color++; }
		else if (temp == reverse_color || temp == -1) { count_other_color++; }
		
	}
	for (i = -1; i > -6; i--)
	{
		// left move
		pointer_l = i;
		temp = brda->get_board_from_pair(std::pair<int, int>(f + f_change * i, s + s_change * i));
		if (temp == EMPTY)
		{
			if (count_empty_l == 1) { break; }
			else { count_empty_l++; continue; }
		}
		else if (temp == color) { count_color++; }
		else if (temp == reverse_color || temp == -1) { count_other_color++; }
	}
	//std::cout << "DEBUG : count_color = " << count_color << std::endl;
	//std::cout << "DEBUG : pointer_r = " << pointer_r << " , pointer_l = " << pointer_l << std::endl;
	//std::cout << "DEBUG : count_other_color = " << count_other_color << std::endl;
	if (count_color == 3)
	{
		if (pointer_r - pointer_l == 6)
		{
			if (pointer_r != 3 || pointer_l != -3)
			{
				if (count_other_color > 0)
				{
					//std::cout << "DEBUG : return 1" << std::endl;
					return 1;
				}
			}
		}
	}
	t1 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (-2), s + s_change * (-2)));
	t2 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (-1), s + s_change * (-1)));
	t3 = brda->get_board_from_pair(std::pair<int, int>(f, s));
	t4 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (1), s + s_change * (1)));
	t5 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (2), s + s_change * (2)));
	if (t1 == EMPTY && t1 == t5 && t2 == color && t2 == t3 && t3 == t4) return 1;

	//std::cout << "DEBUG : return 0" << std::endl;
	return 0;
	
}

int ai::is_d3_wrap(board *brda, int addr, int color)
{
	return is_d3_new_method(brda, addr, color);
	//return is_d3_future(brda, addr, color);
}

int ai::pick(board *bbb, int color)
{
	//wrapper
	int r = ai_shallow_search(bbb, color);
	if(r == -1)	return simple_pick(bbb->brd);
	else return r;
}

int ai::simple_pick(bb *b)
{
	// return first empty address
	// if board is full, return -1;
	int i;
	for (i = 0; i < (int)(b->size()); i++) if (b->at(i) == EMPTY) return i;
	return -1;
}

int ai::value_when_applied(board *brda, int addr, int color)
{
	brda->set_board_safe(addr, color);
	int r = board_value(brda, color);
	brda->set_board(addr, EMPTY);
	return r;
}

int ai::board_value(board *brda, int color)
{
	lines *ll = new lines();
	ll->full_update(brda->brd);
	int r = lines_value(ll, color);
	ll->~lines();
	return r;
}

int ai::lines_value(lines *cur_l, int color)
{
	// it returns the value of whole board's score.
	int i, sum;
	sum = 0;
	if (color == BLACK)
	{
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += black_ai_value_factor(cur_l->horlines->at(i));
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += black_ai_value_factor(cur_l->verlines->at(i));
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += black_ai_value_factor(cur_l->sshlines->at(i));
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += black_ai_value_factor(cur_l->bshlines->at(i));
	}
	else if (color == WHITE)
	{
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += white_ai_value_factor(cur_l->horlines->at(i));
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += white_ai_value_factor(cur_l->verlines->at(i));
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += white_ai_value_factor(cur_l->sshlines->at(i));
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += white_ai_value_factor(cur_l->bshlines->at(i));
	}
	return sum;
}

int ai::black_ai_value_factor(int size)
{
	// it's weighted value of the line.
	// if inappropriate input comes, it returns 0
	// it is biased value for BLACK AI.
	// it assumes the 'size' parameter has the value between -1 * LINESIZE and LINESIZE

	//white line
	if (size < 0 && size >= (-1) * LINESIZE) 
	{
		if (size == (-1) * LINESIZE) return -10000;
		else return (int)((-1) * std::pow(B_WL, (-1) * size));
	}
	//black line
	else if (size >= 0 && size <= LINESIZE) 
	{
		if (size == LINESIZE) return 100000;
		return (int)(std::pow(B_BL, (double)size)); 
	}
	else return 0;
}

int ai::white_ai_value_factor(int size)
{
	// it's weighted value of the line.
	// if inappropriate input comes, it returns 0
	// it is biased value for WHITE AI.
	// it assumes the 'size' parameter has the value between -1 * LINESIZE and LINESIZE

	//white line
	if (size < 0 && size >= (-1) * LINESIZE)
	{
		if (size == (-1) * LINESIZE) return 100000;
		else return (int)(std::pow(W_WL, (-1) * size));
	}
	//black line
	else if (size > 0 && size <= LINESIZE)
	{
		if (size == LINESIZE) return -10000;
		return (int)((-1) * std::pow(W_BL, (double)size));
	}
	else return 0;
}

int ai::ai_shallow_search(board *brda, int color)
{
	// Purpose : Testing time consume of depth 1 search
	// function : choose best address
	int i;
	std::vector<int> addrs = available_addrs(brda, color);
	int max, temp, raddr;
	if (brda->is_board_empty()) return (BRDSIZE / 2) * BRDSIZE + (BRDSIZE / 2);
	else if ((int)addrs.size() == 0) return -1;
	max = value_when_applied(brda, addrs[0], color);
	raddr = addrs[0];
	for (i = 1; i < (int)addrs.size(); i++)
	{
		temp = value_when_applied(brda, addrs[i], color);
		if (max < temp)
		{
			max = temp;
			raddr = addrs[i];
		}
	}
	return raddr;
}

std::vector<int> ai::available_addrs(board *brda, int color)
{
	std::vector<int> empty_addrs = brda->empty_addrs();
	int i;
	std::vector<int> r;
	for (i = 0; i < (int)empty_addrs.size(); i++)
		if (is_d3_wrap(brda, empty_addrs[i], color) == 0)
			r.push_back(empty_addrs[i]);
	return r;
}