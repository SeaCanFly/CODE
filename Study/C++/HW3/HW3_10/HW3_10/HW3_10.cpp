/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_10
Visual Studio 2015
*/

#include<iostream>
#include"HW3_10.h"
using namespace std;
int main()
{
	Ram ram;
	ram.write(100, 20);
	ram.write(101, 30);
	char res = ram.read(100) + ram.read(101);
	ram.write(102, res);
	cout << "102:" << (int)ram.read(102) << endl;
	return 0;
}