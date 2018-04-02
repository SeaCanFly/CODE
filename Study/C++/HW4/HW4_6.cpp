/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #4_6
Visual Studio 2015
*/
#include<iostream>
#include"HW4_6.h"
using namespace std;
int main()
{
	int num,count=0;
	cout << "input the number of circles>>";
	cin >> num;
	Circle* p = new Circle[num-1];
	for(int i=0;i<num;i++)
	{
		int radius;
		cout << "Circle " << i << "radius>>";
		cin >> radius;
		p[i].setRadius(radius);
		if (p[i].getArea() >= 100.0)
		{
			count++;
		}
	}
	cout << "Area greater than 100 = " << count << endl;
	return 0;
}