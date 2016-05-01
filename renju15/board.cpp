#include "board.h"

board::board()
{
	brd = new bb(BRDSIZE*BRDSIZE);
}

board::~board()
{
	brd->~vector();
}

int board::color_sanity(int color)
{
	// if color is EMPTY or BLACK or WHITE, return 1. Otherwise, return 0.
	if (color == EMPTY || color == BLACK || color == WHITE) return 1;
	else return 0;
}

int board::addr_sanity(int addr)
{
	// if addr is in brd's size, return 1.
	// Otherwise, return 0
	if (addr >= 0 && addr < (BRDSIZE * BRDSIZE))
	{
		return 1;
	}
	return 0;
}

int board::str2addr(std::string str)
{
	// convert string to address
	// Only works when BRDSIZE == 15
	// if it is inappropriate input string, return -1
	int two_or_three = (int)str.length();
	int f, s, t;
	if (two_or_three == 2)
	{
		f = (int)str.at(0) - (int)'A';
		s = (int)str.at(1) - (int)'1';
		if (f < 0 || f >= BRDSIZE || s < 0 || s >= BRDSIZE) return -1;
		else return s * BRDSIZE + f;
	}
	else if (two_or_three == 3)
	{
		f = (int)str.at(0) - (int)'A';
		s = (int)str.at(1) - (int)'1';
		t = (int)str.at(2) - (int)'0';
		if (f < 0 || f >= BRDSIZE || s != 0 || t < 0 || t >= 6) return -1;
		else return (10 + t - 1) * BRDSIZE + f;
	}
	else
	{
		return -1;
	}
}

std::string board::addr2string(int addr)
{
	// it is not general purpose function. it works well when BRDSIZE == 15
	char f [3];
	f[0] = (char)(addr % BRDSIZE + (int)'A');
	if (addr / BRDSIZE > 8 && addr / BRDSIZE < BRDSIZE)
	{
		f[1] = '1';
		f[2] = (char)(addr / BRDSIZE - 9 + (int)'0');

	}
	else if(addr / BRDSIZE > -1 && addr / BRDSIZE < 9)
	{
		f[1] = (char)(addr / BRDSIZE + (int)'1');
		f[2] = ' ';
	}
	else
	{
		f[1] = 'Q';
		f[2] = 'Q';
	}
	return std::string(f, 3);
}

int board::reverse_color(int color)
{
	// BLACK -> WHITE
	// WHITE -> BALCK
	// else, return EMPTY
	if (color == BLACK) return WHITE;
	else if (color == WHITE) return BLACK;
	else return EMPTY;
}

int board::set_board(int addr, int color)
{
	// set board.

	// if addr_sanity fails, do not change board and return -2.
	// if color_sanity fails, return -1.
	// if board changed, return 0

	if (!addr_sanity(addr))	return -2;
	else if (!color_sanity(color)) return -1;
	else
	{
		brd->at(addr) = color;
		return 0;
	}
}

int board::set_board_safe(int addr, int color)
{
	// set board if and only if brd->at(addr) == EMPTY

	// if addr_sanity fails, do not change board and return -2.
	// if color_sanity fails, return -1.
	// if board not changed, return 1.
	// if board changed, return 0
	if (!addr_sanity(addr))	return -2;
	else if (!color_sanity(color)) return -1;
	else if (brd->at(addr) != EMPTY) return 1;
	else
	{
		brd->at(addr) = color;
		return 0;
	}
}

int board::get_board_safe(int addr)
{
	//if addr is out of range, return -1
	// else, return EMPTY, BLACK, or WHITE
	if (addr < 0 || addr >= (BRDSIZE * BRDSIZE)) return -1;
	else return brd->at(addr);
}

int board::is_board_full()
{
	//if board full, return 1
	//else, return 0
	int i;
	for (i = 0; i < BRDSIZE * BRDSIZE; i++) if (brd->at(i) == EMPTY) return 0;
	return 1;
}

int board::is_board_empty()
{
	// if board all empty, return 1
	//else, return 0
	int i;
	for (i = 0; i < BRDSIZE * BRDSIZE; i++) if (brd->at(i) != EMPTY) return 0;
	return 1;
}

int board::board_print()
{
	int i;
	std::cout << std::endl << "    ";
	for (i = 0; i < BRDSIZE; i++) { std::cout << (char)(i + (int)'A') << " "; }
	std::cout << std::endl;
	board_print_up();
	for (i = BRDSIZE - 2; i > 0; i--) { board_print_body(i); }
	board_print_down();
	std::cout << "    ";
	for (i = 0; i < BRDSIZE; i++) { std::cout << (char)(i + (int)'A') << " "; }
	std::cout << std::endl << std::endl;

	return 0;
}

int board::board_print_base(int n, std::string firststr, std::string bodystr, std::string laststr)
{
	int temp_first, temp, temp_last, i;
	std::cout.width(3);
	std::cout << n + 1;
	temp_first = brd->at(n * BRDSIZE);
	temp_last = brd->at(n * BRDSIZE + (BRDSIZE - 1));
	if (temp_first == EMPTY) std::cout << firststr;
	else std::cout << bw_string(temp_first);
	for (i = 1; i < BRDSIZE - 1; i++)
	{
		temp = brd->at(n * BRDSIZE + i);
		if (temp == EMPTY) std::cout << bodystr;
		else std::cout << bw_string(temp);
	}
	if (temp_last == EMPTY) std::cout << laststr;
	else std::cout << bw_string(temp_last);
	std::cout.width(3);
	std::cout << n + 1 << std::endl;

	return 0;
}

int board::board_print_up() { return board_print_base(BRDSIZE - 1, "¦£", "¦¨", "¦¤"); }

int board::board_print_down() { return board_print_base(0, "¦¦", "¦ª", "¦¥"); }

int board::board_print_body(int n) { return board_print_base(n, "¦§", "¦«", "¦©"); }

std::string board::bw_string(int color)
{
	// if color is BLACK, return "¡Û"
	// else if color is WHITE, return "¡Ü"
	// else, return " "
	if (color == BLACK) return "¡Û";
	else if (color == WHITE) return "¡Ü";
	else return " ";
}

std::vector<int> board::empty_addrs()
{
	int i;
	std::vector<int> r;
	for (i = 0; i < BRDSIZE * BRDSIZE; i++)
		if (get_board_safe(i) == EMPTY)
			r.push_back(i);
	return r;
}

std::pair<int, int> board::addr2pair(int addr) 
{
	//for bad input, it returns (-1, -1)
	if (!addr_sanity(addr)) return std::pair<int, int>(-1, -1);
	else return std::pair<int, int>(addr / BRDSIZE, addr % BRDSIZE);
}

int board::pair2addr(std::pair<int, int> p)
{
	//for bad input, it returns -1
	if (p.first < 0 || p.first >= BRDSIZE) return -1;
	else if (p.second < 0 || p.second >= BRDSIZE) return -1;
	else return p.first * BRDSIZE + p.second;
}

int board::get_board_from_pair(std::pair<int, int> p)
{
	//if addr is out of range, return -1
	// else, return EMPTY, BLACK, or WHITE
	return get_board_safe(pair2addr(p));
}