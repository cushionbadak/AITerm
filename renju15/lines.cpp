#include "lines.h"
#include "board.h"

lines::lines()
{
	horlines = new std::vector<int>(UNITSIZE * BRDSIZE);
	verlines = new std::vector<int>(UNITSIZE * BRDSIZE);
	sshlines = new std::vector<int>(UNITSIZE * UNITSIZE);
	bshlines = new std::vector<int>(UNITSIZE * UNITSIZE);
}

lines::~lines()
{
	horlines->~vector();
	verlines->~vector();
	sshlines->~vector();
	bshlines->~vector();
}

// __start : return start addr
// if n is inappropriate input, it returns -1
int lines::hor_start(int n)
{
	if (n < 0 || n >= UNITSIZE * BRDSIZE) return -1;
	else return (n / UNITSIZE) * BRDSIZE + n % UNITSIZE;
}

int lines::ver_start(int n)
{
	if (n < 0 || n >= UNITSIZE * BRDSIZE) return -1;
	else return (n / BRDSIZE) * BRDSIZE + n % BRDSIZE;
}

int lines::ssh_start(int n)
{
	if (n < 0 || n >= UNITSIZE * UNITSIZE) return -1;
	else return (n / UNITSIZE) * BRDSIZE + n % UNITSIZE;
}

int lines::bsh_start(int n)
{
	if (n < 0 || n >= UNITSIZE * UNITSIZE) return -1;
	else return (n / UNITSIZE) * BRDSIZE + n % UNITSIZE + 4;
}

// __set : calculate line's value
// if inappropriate n given, it returns -1
int lines::setline_base(int n, bb *b, int iter_v)
{
	// n : line number n, 
	int black = 0; int white = 0; int s = hor_start(n);
	int i, temp; //iterator, temp
	if (s == -1) return -1;
	for (i = 0; i < LINESIZE; i++)
	{
		temp = b->at(s + i * (iter_v));
		if (temp == BLACK) black++;
		else if (temp == WHITE) white++;
	}
	horlines->at(n) = xor_bw(black, white);
	return 0;
}

int lines::hor_setline(int n, bb *b) { return setline_base(n, b, 1); }

int lines::ver_setline(int n, bb *b) { return setline_base(n, b, BRDSIZE); }

int lines::ssh_setline(int n, bb *b) { return setline_base(n, b, (BRDSIZE + 1)); }

int lines::bsh_setline(int n, bb *b) { return setline_base(n, b, (BRDSIZE - 1)); }

int lines::xor_bw(int b, int w)
{
	//return b if w = 0
	//return (-1 * w) if b = 0
	//else, return 0
	if (w == 0) return b;
	else if (b == 0) return (-1) * w;
	else return 0;
}

int lines::full_update(bb *b)
{
	// it can be improved
	int i;
	for (i = 0; i < UNITSIZE * BRDSIZE; i++) hor_setline(i, b);
	for (i = 0; i < UNITSIZE * BRDSIZE; i++) ver_setline(i, b);
	for (i = 0; i < UNITSIZE * UNITSIZE; i++) ssh_setline(i, b);
	for (i = 0; i < UNITSIZE * UNITSIZE; i++) bsh_setline(i, b);
	return 0;
}

int lines::count(int color, int size)
{
	// when error, return -1;
	// else count from all lines
	int i;
	int sum = 0;
	int value = csv(color, size);
	if (value == -10) return -1;
	for (i = 0; i < horlines->size(); i++) if (horlines->at[i] == value) sum++;
	for (i = 0; i < verlines->size(); i++) if (verlines->at[i] == value) sum++;
	for (i = 0; i < sshlines->size(); i++) if (sshlines->at[i] == value) sum++;
	for (i = 0; i < bshlines->size(); i++) if (bshlines->at[i] == value) sum++;

	return sum;
}

int lines::countover(int color, int size)
{
	//count from size+1 to LINESIZE
	int i;
	int sum = 0;
	if (csv(color, size) == -10) return -1;
	for (i = size + 1; i <= LINESIZE; i++) sum += count(color, i);
	
	return sum;
}

int lines::countunder(int color, int size)
{
	//count from size-1 to 0
	int i;
	int sum = 0;
	if (csv(color, size) == -10) return -1;
	for (i = size -1; i >= 0; i--) sum += count(color, i);

	return sum;
}

int lines::black_win()
{
	// if black wins, it returns 1;
	// else, return 0.
	if (count(BLACK, 5) > 0) return 1;
	else return 0;
}

int lines::white_win()
{
	// if white wins, it returns 1;
	// else, return 0.
	if (count(WHITE, 5) > 0) return 0;
	else return 0;
}

int lines::csv(int color, int size)
{
	// when error, it returns -10
	if (color == BLACK) return size;
	else if (color == WHITE) return size * (-1);
	else return -10;
}