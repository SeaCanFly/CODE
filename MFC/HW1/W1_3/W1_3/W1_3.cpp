/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #1_3
Visual Studio 2015
*/

#include"W1_3.h"
MyTime::MyTime() 
{ 
	hour = 0; minute = 0; second = 0; 
}
MyTime::MyTime(int h, int m, int s)
{
	if (s >= 60)
	{
		m = m + s / 60;
		s = s % 60;
	}
	if (m >= 60)
	{
		h = h + m / 60;
		m = m % 60;
	}
	hour = h;
	minute = m;
	second = s;
}
void MyTime::print()
{
	cout << hour << ":" << minute << ":" << second << endl;
}
MyTime MyTime::add(MyTime a)
{
	hour = hour + a.hour;
	minute = minute + a.minute;
	second = second + a.second;
	*this = MyTime(hour, minute, second);
	return *this;
}
int main()
{
	MyTime a(0, 70, 90);
	MyTime b(0, 0, 3630);

	a.print();
	b.print();

	a.add(b);
	a.print();

	return 0;
}