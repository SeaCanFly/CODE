/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_6
Visual Studio 2015
*/

#include<iostream>
#include"HW3_6.h"
using namespace std;
int main()
{
	Integer n(30);
	cout << n.get() << ' ';
	n.set(50);
	cout << n.get() << ' ';

	Integer m("300");
	cout << m.get() << ' ';
	cout << m.isEven()<<endl;
	return 0;
}