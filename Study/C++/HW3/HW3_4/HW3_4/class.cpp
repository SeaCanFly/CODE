#include "HW3_4.h"
#include<ctime>
#include<cstdlib>
EvenRandom::EvenRandom()
{
	srand((unsigned)time(0));
	num = rand();
}
int EvenRandom::next()
{
	do {
		num = rand();
	} while (num % 2 != 0);
	return num;
}
int EvenRandom::even(int pnum, int tnum)
{
	do {
		num = (rand() % (tnum - pnum + 1)) + pnum;
	} while (num % 2 != 0);
	return num;
}