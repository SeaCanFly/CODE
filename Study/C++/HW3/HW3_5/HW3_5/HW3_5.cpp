/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_5
Visual Studio 2015
*/

#include<iostream>
#include"HW3_5.h"
using namespace std;
int main()
{
	SelectableRandom r;
	cout << "\"0--" << RAND_MAX << "\" " << "10 random even integers" << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = r.even();
		cout << n << ' ';
	}
	cout << endl << endl << "\"2--10\"" << "10 random odd integers" << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = r.odd(2, 10);
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}