/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_8
Visual Studio 2015
*/

#include<iostream>
#include"HW3_8.h"
using namespace std;
int main()
{
	while (1)
	{ 
		Add a;
		Sub s;
		Mul m;
		Div d;
		int x = 0, y = 0; char c;
		cout << "Input two numbers and operator>>";
		cin >> x >> y >> c;
		switch (c)
		{
		case '+': a.setValue(x, y);
			cout << a.calculate() << endl; break;
		case '-':s.setValue(x, y);
			cout << s.calculate() << endl; break;
		case '*':m.setValue(x, y);
			cout << m.calculate() << endl; break;
		case '/':d.setValue(x, y);
			cout << d.calculate() << endl; break;
		default:
			break;
		}
	}

	return 0;
}