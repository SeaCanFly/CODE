#pragma once
#include"shape.h"
class Rect :public Shape
{
private:
	float w, h;
public:
	Rect(float fx, float fy, float fw, float fh) :Shape(fx, fy), w(fw), h(fh) {}
	virtual void fdraw(HWND,HDC);
};