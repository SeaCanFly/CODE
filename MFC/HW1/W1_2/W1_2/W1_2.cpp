/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_2
Visual Studio 2015
*/

#include"W1_2.h"
CMyPoint::CMyPoint()
{
	x = 0; 
	y = 0;
}
CMyPoint::CMyPoint(int ix, int iy)
{
	x = ix;
	y = iy;
}
void CMyPoint::print()
{
	cout << "(" << x << "," << y << ")" << endl;
}
float CMyPoint::distance(CMyPoint a)
{
	return sqrt((x - a.x)*(x - a.x) + (y - a.y)*(y - a.y));
}
int main()
{
	CMyPoint a(4, 5);
	CMyPoint b(1, 1);

	a.print();
	b.print();

	cout << "The distance between a and b:" << a.distance(b) << endl;

	return 0;
}