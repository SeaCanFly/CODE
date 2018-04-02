#pragma once
#include<iostream>
#include<string>
using namespace std;
class Point
{
	int mi_x, mi_y;
protected:
	void fMove(int i_x, int i_y)
	{
		mi_x = i_x;
		mi_y = i_y;
	}
public:
	Point(int i_x,int i_y):mi_x(i_x),mi_y(i_y){}
	int getX() { return mi_x; }
	int getY() { return mi_y; }
};
class ColorPoint :public Point
{
	string ms_clr;
public:
	ColorPoint(int i_x,int i_y,string s_clr):Point(i_x,i_y),ms_clr(s_clr){}
	void setPoint(int i_x, int i_y){fMove(i_x, i_y);}
	void setColor(string s_clr) { ms_clr = s_clr; }
	void fShow()
	{
		cout << ms_clr << " " << "(" << getX() << "," << getY() << ")" << endl;
	}
};