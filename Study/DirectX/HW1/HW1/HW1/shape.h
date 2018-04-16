#pragma once
#include<cstdio>
#include<Windows.h>
class Shape
{
protected:
	float x, y;
public:
	Shape(float fx, float fy) :x(fx), y(fy) {}
	virtual ~Shape(){}
	virtual	void fdraw(HWND,HDC);
};
