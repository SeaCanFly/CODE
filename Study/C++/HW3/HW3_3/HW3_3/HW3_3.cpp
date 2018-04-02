/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_3
Visual Studio 2015
*/

#include<iostream>
#include"HW3_3.h"
using namespace std;
int main()
{
	Random r;
	cout << "\"0--" << RAND_MAX << "\" " << "10 random integers" << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = r.next();
		cout << n << ' ';
	}
	cout << endl << endl << "\"2--4\"" << "10 random integers" << endl;
	for (int i = 0; i < 10; i++)
	{
		int n = r.nextInRange(2, 4);
		cout << n << ' ';
	}
	cout << endl;
	return 0;
}