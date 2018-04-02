/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_7
Visual Studio 2015
*/

#include<iostream>
#include"HW3_7.h"
using namespace std;
int main()
{
	Oval a, b(3, 4);
	a.set(10, 20);
	a.show();
	cout << b.getWidth() << ';' << b.getHeight() << endl;
	return 0;
}