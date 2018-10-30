/*
Name:WangYiSen
Student Id:B577046
Game Software
HomeWork #4_1
Visual Studio 2015
*/
#include<iostream>
using namespace std;

class Color
{
private:
	int red, green, blue;
public:
	Color() :red(0), green(0), blue(0) {};
	Color(int r, int g, int b) :red(r), green(g), blue(b) {};
	void setColor(int r, int g, int b) { red = r; green = g; blue = b; }
	void doShow() { cout << red << ' ' << green << ' ' << blue << endl; }

};
int main()
{
	Color screen_color(255, 0, 0);
	Color* p;
	p = &screen_color;
	p->doShow();
	Color colors[3];
	p = colors;
	p[0].setColor(255, 0, 0);
	p[1].setColor(0, 255, 0);
	p[2].setColor(0, 0, 255);
	for (int i = 0; i < 3; i++)
	{
		p[i].doShow();
	}
	return 0;
}