/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #3_2
Visual Studio 2015
*/

#include<iostream>
#include"HW3_2.h"
using namespace std;
int main()
{
	Date birth(2014, 3, 20);
	Date independenceDay("1941/8/15");
	independenceDay.show();
	cout << birth.getYear() << ',' << birth.getMonth() << ',' << birth.getDay() << endl;
	return 0;
}