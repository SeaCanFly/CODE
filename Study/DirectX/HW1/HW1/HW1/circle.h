#pragma once
#include"shape.h"
class Circle :public Shape
{
private:
	float r;
public:
	Circle(float fx, float fy, float fr) :Shape(fx, fy), r(fr) {}
	virtual void fdraw(HWND,HDC);
};