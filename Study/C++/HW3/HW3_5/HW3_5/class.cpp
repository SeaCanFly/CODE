#include "HW3_5.h"
#include<ctime>
#include<cstdlib>
SelectableRandom::SelectableRandom()
{
	srand((unsigned)time(0));
	num = rand();
}
int SelectableRandom::even()
{
	do {
		num = rand();
	} while (num % 2 != 0);
	return num;
}
int SelectableRandom::odd(int pnum, int tnum)
{
	do {
		num = rand() % (tnum - pnum + 1) + pnum;
	} while (num % 2 == 0);
	return num;
}