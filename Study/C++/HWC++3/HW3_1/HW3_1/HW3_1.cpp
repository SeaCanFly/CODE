/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_1
Visual Studio 2015
*/

#include<iostream>
#include"HW3_1.h"
using namespace std;
int main()
{
	Tower myTower;
	Tower seoulTower(100);
	cout << "Height:" << myTower.getHeight() << "m" << endl;
	cout << "Height:" << seoulTower.getHeight() << "m" << endl;
	return 0;
}