/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_4
Visual Studio 2015
*/

#include<iostream>
#include"HW3_4.h"
using namespace std;
int main()
{
	EvenRandom r;
	cout << "\"0--" << RAND_MAX << "\" " << "10 random even integers" << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = r.next();
		cout << n << ' ';
	}
	cout << endl << endl << "\"2--10\"" << "10 random even integers" << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = r.even(2, 10);
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}