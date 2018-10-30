/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #9_7
Visual Studio 2015
*/
#include"hw9_7.h"
int main()
{
	Shape* p[3];
	p[0] = new Oval("Pancake",10,20);
	p[1] = new Rect("Glutinous rice cake", 30, 40);
	p[2] = new Triangular("Toast", 30, 40);
	for (int i = 0; i < 3; i++)
	{
		cout << p[i]->getName() << " Area=" << p[i]->getArea() << endl;
	}
	for (int i = 0; i < 3; i++)
	{
		delete p[i];
	}
	return 0;
}