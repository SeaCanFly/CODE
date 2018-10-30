/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #9_5
Visual Studio 2015
*/
#include"hw9_5.h"
#include<iostream>
using namespace std;
int main()
{
	ANDGate and;
	ORGate  or;
	XORGate xor;

	and.set(true, false);
	or .set(true, false);
	xor.set(true, false);
	cout.setf(ios::boolalpha);
	cout << and.operation() << endl;
	cout << or .operation() << endl;
	cout << xor.operation() << endl;
	return 0;
}