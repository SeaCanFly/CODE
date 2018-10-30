/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #10_7
Visual Studio 2015
*/
#include<iostream>
using namespace std;
class Circle
{
	int radius;
public:
	Circle(int radius = 1) { this->radius = radius; }
	int getRadius() { return radius; }
};
template<class T>
T bigger(T a, T b)
{
	if (a > b)return a;
	else return b;
}
int main()
{
	int a = 20, b = 50, c;
	c = bigger(a, b);
	cout << "20,50, bigger:" << c << endl;
	Circle waffle(10), pizza(20), y;
	y = bigger(waffle.getRadius(), pizza.getRadius());
	cout << "waffle,pizza, bigger:" << y.getRadius() << endl;
	return 0;
}