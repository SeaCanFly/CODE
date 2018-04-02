#include"HW3_3.h"
#include<ctime>
#include<cstdlib>
Random::Random()
{
	srand((unsigned)time(0));
	num = rand();
}
int Random::next()
{
	return num = rand();
}
int Random::nextInRange(int pnum, int tnum)
{
	return num = (rand() % (tnum - pnum + 1)) + pnum;
}