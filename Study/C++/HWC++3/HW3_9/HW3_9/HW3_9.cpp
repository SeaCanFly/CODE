/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_9
Visual Studio 2015
*/

#include<iostream>
#include"HW3_9.h"
using namespace std;
int main()
{
	Box b(10, 2);
	b.draw();
	cout << endl;
	b.setSize(7, 4);
	b.setFill('^');
	b.draw();
	return 0;
}