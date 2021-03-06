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
	if (counter > 1)
	{
		brda->set_board(addr, EMPTY);
		// board returned to original board.
		return 1;
	}
	counter += is_d3_new_method_sub(brda, center, color, 1, 1);
	if (counter > 1)
	{
		brda->set_board(addr, EMPTY);
		// board returned to original board.
		return 1;
	}
	counter += is_d3_new_method_sub(brda, center, color, 1, -1);

	// board returned to original board.
	brda->set_board(addr, EMPTY);
	if (counter > 1)
	{
		return 1;
	}
	else return 0;
}

int ai::is_d3_new_method_sub(board *brda, std::pair<int, int> center, int color, int f_change, int s_change)
{
	// check 3 for only two direction from center.
	// if 3 -> return 1, else, return 0.
	// center's color must be equal to argument 'color'

	// t4 is center
	int t0, t1, t2, t3, t4, t5, t6, t7, t8;
	int f = center.first;
	int s = center.second;
	
	t0 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (-4), s + s_change * (-4)));
	t1 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (-3), s + s_change * (-3)));
	t2 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (-2), s + s_change * (-2)));
	t3 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (-1), s + s_change * (-1)));
	t4 = brda->get_board_from_pair(std::pair<int, int>(f, s));
	t5 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (1), s + s_change * (1)));
	t6 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (2), s + s_change * (2)));
	t7 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (3), s + s_change * (3)));
	t8 = brda->get_board_from_pair(std::pair<int, int>(f + f_change * (4), s + s_change * (4)));

	// most important check -- double 3 in one line
	if (t8 == EMPTY && t7 == color && t6 == color && t5 == EMPTY && t4 == color && t3 == EMPTY && t2 == color && t1 == color && t0 == EMPTY) return 2;
	if (t1 == EMPTY && t2 == color && t3 == EMPTY && t4 == color && t5 == color && t6 == EMPTY && t7 == color && t8 == EMPTY) return 2;
	if (t0 == EMPTY && t1 == color && t2 == EMPTY && t3 == color && t4 == color && t5 == EMPTY && t6 == color && t7 == EMPTY) return 2;

	if (t1 == EMPTY && t1 == t5 && t2 == color && t2 == t3 && t3 == t4 && t0 != color && t6 != color && (t0 == EMPTY || t6 == EMPTY)) return 1;
	if (t2 == EMPTY && t2 == t6 && t3 == color && t3 == t4 && t4 == t5 && t1 != color && t7 != color && (t1 == EMPTY || t7 == EMPTY)) return 1;
	if (t3 == EMPTY && t3 == t7 && t4 == color && t4 == t5 && t5 == t6 && t2 != color && t8 != color && (t2 == EMPTY || t8 == EMPTY)) return 1;

	if (t0 == EMPTY && t1 == color && t2 == t1 && t4 == t2 && t3 == EMPTY && t5 == EMPTY) return 1;
	if (t2 == EMPTY && t3 == color && t4 == t3 && t6 == t4 && t5 == EMPTY && t7 == EMPTY) return 1;
	if (t3 == EMPTY && t4 == color && t5 == t4 && t7 == t5 && t6 == EMPTY && t8 == EMPTY) return 1;

	if (t0 == EMPTY && t1 == color && t2 == EMPTY && t3 == color && t4 == color && t5 == EMPTY) return 1;
	if (t1 == EMPTY && t2 == color && t3 == EMPTY && t4 == color && t5 == color && t6 == EMPTY) return 1;
	if (t3 == EMPTY && t4 == color && t5 == EMPTY && t6 == color && t7 == color && t8 == EMPTY) return 1;

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
	int r = ai_minmax_search(bbb, color, SEARCH_DEPTH);
	if (r == -1)
	{
		return simple_pick(bbb->brd);
	}
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

int ai::value_when_applied(board *brda, int addr, int color, int depthflag)
{
	brda->set_board_safe(addr, color);
	int r = board_value(brda, color, depthflag);
	brda->set_board(addr, EMPTY);
	return r;
}

int ai::board_value(board *brda, int color, int depthflag)
{
	lines *ll = new lines();
	ll->full_update(brda->brd);
	int r = lines_value(ll, color, depthflag);
	ll->~lines();
	return r;
}

int ai::lines_value(lines *cur_l, int color, int depthflag)
{
	// it returns the value of whole board's score.
	int i, sum;
	sum = 0;
	if (color == BLACK)
	{
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += black_ai_value_factor(cur_l->horlines->at(i), depthflag);
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += black_ai_value_factor(cur_l->verlines->at(i), depthflag);
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += black_ai_value_factor(cur_l->sshlines->at(i), depthflag);
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += black_ai_value_factor(cur_l->bshlines->at(i), depthflag);
	}
	else if (color == WHITE)
	{
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += white_ai_value_factor(cur_l->horlines->at(i), depthflag);
		for (i = 0; i < UNITSIZE * BRDSIZE; i++) sum += white_ai_value_factor(cur_l->verlines->at(i), depthflag);
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += white_ai_value_factor(cur_l->sshlines->at(i), depthflag);
		for (i = 0; i < UNITSIZE * UNITSIZE; i++) sum += white_ai_value_factor(cur_l->bshlines->at(i), depthflag);
	}
	return sum;
}

int ai::black_ai_value_factor(int size, int depthflag)
{
	// it's weighted value of the line.
	// if inappropriate input comes, it returns 0
	// it is biased value for BLACK AI.
	// it assumes the 'size' parameter has the value between -1 * LINESIZE and LINESIZE

	//white line
	if (size < 0 && size >= (-1) * LINESIZE)
	{
		if (size == (-1) * LINESIZE) return -1000000;
		else return (int)((-1) * std::pow(B_WL, (-1) * size));
	}
	//black line
	else if (size >= 0 && size <= LINESIZE)
	{
		if (size == LINESIZE)
		{
			if (depthflag) return 10000000;
			else return 10000000;
		}
		return (int)(std::pow(B_BL, (double)size));
	}
	else return 0;
}

int ai::white_ai_value_factor(int size, int depthflag)
{
	// it's weighted value of the line.
	// if inappropriate input comes, it returns 0
	// it is biased value for WHITE AI.
	// it assumes the 'size' parameter has the value between -1 * LINESIZE and LINESIZE

	//white line
	if (size < 0 && size >= (-1) * LINESIZE)
	{
		if (size == (-1) * LINESIZE)
		{
			if (depthflag) return 10000000;
			else return 10000000;
		}
		else return (int)(std::pow(W_WL, (-1) * size));
	}
	//black line
	else if (size > 0 && size <= LINESIZE)
	{
		if (size == LINESIZE) return -1000000;
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
	max = value_when_applied(brda, addrs[0], color, 0);
	raddr = addrs[0];
	for (i = 1; i < (int)addrs.size(); i++)
	{
		temp = value_when_applied(brda, addrs[i], color, 0);
		if (max < temp)
		{
			max = temp;
			raddr = addrs[i];
		}
	}
	return raddr;
}

int ai::ai_minmax_search(board *brda, int color, int depth)
{
	// it returns address.
	// color : next stone's color. Same meaning with ai_shallow_search's 'color' argument.
	// if color is black, it always pick larger one.
	// if color is white, it always pick smaller one.
	// if color is EMPTY or inappropriate one, it gives -1.
	// remain_depth must be over 0.
	int i, temp, max, r;
	std::vector<int> addrs;
	std::vector<std::pair<int, int>> s_addrs;	// top 5 addrs. vector of (address, board_value)
	r = -1;
	max = 0;
	if (brda->is_board_empty()) return (BRDSIZE / 2) * BRDSIZE + (BRDSIZE / 2);
	else if (depth <= 0) return -1;
	else if (color != BLACK && color != WHITE) return -1;
	else
	{
		addrs = available_addrs(brda, color);
		if (depth <= 0) return -1;
		else if ((int)addrs.size() == 0) return -1;
		else
		{
			// around MAX
			for (i = 0; i < (int)addrs.size(); i++)
			{
				temp = value_when_applied(brda, addrs[i], color, 0);
				if ((int)s_addrs.size() < S_ADDRS_SIZE)
				{
					s_addrs.push_back(std::pair<int, int>(addrs[i], temp));
				}
				else
				{
					v_pair_sort(&s_addrs);
					if (s_addrs[S_ADDRS_SIZE - 1].second < temp)
					{
						s_addrs[S_ADDRS_SIZE - 1] = std::pair<int, int>(addrs[i], temp);
					}
				}
			}
			// MAX
			for (i = 0; i < (int)s_addrs.size(); i++)
			{
				brda->set_board_safe(s_addrs[i].first, color);
				temp = ai_minmax_value(brda, brda->reverse_color(color), color, depth - 1);
				if (i == 0 || max < temp)
				{
					max = temp;
					r = s_addrs[i].first;
				}
				brda->set_board(s_addrs[i].first, EMPTY);
			}
		}
	}
	return r;
}

int ai::ai_minmax_value(board *brda, int color, int ori_color, int remain_depth)
{
	// it returns board value.
	// color : next stone's color. it must be BLACK or WHITE
	// if color == ori_color, it picks MAX value, otherwise, it picks MIN value.
	int i, temp, r;
	std::vector<int> addrs = available_addrs(brda, color);
	std::vector<std::pair<int, int>> s_addrs;
	r = 0;
	if (remain_depth <= 0)
	{
		// leaf node
		if (SEARCH_DEPTH < 2) return board_value(brda, ori_color, 0);
		else return board_value(brda, ori_color, 0);
	}
	else
	{
		if (color == ori_color)
		{
			// MAX part
			// around MAX
			for (i = 0; i < (int)addrs.size(); i++)
			{
				temp = value_when_applied(brda, addrs[i], color, 1);
				if ((int)s_addrs.size() < S_ADDRS_SIZE)
				{
					s_addrs.push_back(std::pair<int, int>(addrs[i], temp));
				}
				else
				{
					v_pair_sort(&s_addrs);
					if (s_addrs[S_ADDRS_SIZE - 1].second < temp)
					{
						s_addrs[S_ADDRS_SIZE - 1] = std::pair<int, int>(addrs[i], temp);
					}
				}
			}
			// MAX
			for (i = 0; i < (int)s_addrs.size(); i++)
			{
				brda->set_board_safe(s_addrs[i].first, color);
				temp = ai_minmax_value(brda, brda->reverse_color(color), ori_color, remain_depth - 1);
				if (i == 0 || r < temp)
				{
					r = temp;
				}
				brda->set_board(s_addrs[i].first, EMPTY);
			}
			return r;
		}
		else
		{
			// MIN part
			// around MIN
			for (i = 0; i < (int)addrs.size(); i++)
			{
				temp = value_when_applied(brda, addrs[i], color, 1);
				if ((int)s_addrs.size() < S_ADDRS_SIZE)
				{
					s_addrs.push_back(std::pair<int, int>(addrs[i], temp));
				}
				else
				{
					v_pair_sort(&s_addrs);
					if (s_addrs[0].second > temp)
					{
						s_addrs[0] = std::pair<int, int>(addrs[i], temp);
					}
				}
			}
			// MIN
			for (i = 0; i < (int)s_addrs.size(); i++)
			{
				brda->set_board_safe(s_addrs[i].first, color);
				temp = ai_minmax_value(brda, brda->reverse_color(color), ori_color, remain_depth - 1);
				if (i == 0 || r > temp)
				{
					r = temp;
				}
				brda->set_board(s_addrs[i].first, EMPTY);
			}
			return r;
		}
	}
	//default value, wish never reach.
	return 0;
}

std::vector<int> ai::available_addrs(board *brda, int color)
{
	// return empty and non-double-3 addresses.
	std::vector<int> empty_addrs = brda->empty_addrs();
	int i;
	std::vector<int> r;
	for (i = 0; i < (int)empty_addrs.size(); i++)
		if (avail_optima(brda, i) == 1)
			if (is_d3_wrap(brda, empty_addrs[i], color) == 0)
				r.push_back(empty_addrs[i]);
	return r;
}

int ai::avail_optima(board *brda, int addr)
{
	// avail_optima's semantic is similar with double-3 check
	// it reduces search space

	// if any stone near addr (distance 4), return 1
	// else, return 0
	std::pair<int, int> center = brda->addr2pair(addr);
	int counter = 0;
	int i, j, temp;
	for (i = -1 * AVAIL_OPT; i < AVAIL_OPT + 1; i++)
	{
		for (j = -1 * AVAIL_OPT; j < AVAIL_OPT + 1; j++)
		{
			temp = brda->get_board_from_pair(std::pair<int, int>(center.first + i, center.second + j));
			if (temp == BLACK || temp == WHITE) return 1;
		}
	}
	return 0;
}

int ai::v_pair_sort(std::vector<std::pair<int, int>> *s_addrs)
{
	// selection sort
	// only for S_ADDRS_SIZE
	// bigger one at front
	int i, j, max;
	std::pair<int, int> temp;
	for (i = 0; i < S_ADDRS_SIZE - 1; i++)
	{
		max = i;
		for (j = i + 1; j < S_ADDRS_SIZE; j++)
		{
			if (s_addrs->at(max).second < s_addrs->at(j).second)
			{
				max = j;
			}
		}
		temp = s_addrs->at(max);
		s_addrs->at(max) = s_addrs->at(i);
		s_addrs->at(i) = temp;
	}
	return 0;
}
