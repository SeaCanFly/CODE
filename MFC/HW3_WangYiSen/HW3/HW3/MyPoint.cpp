#include "stdafx.h"
#include "MyPoint.h"


MyPoint::MyPoint()
{
	clr = RGB(0, 0, 0);
	pt = 0;
	rect = 1;
}


MyPoint::~MyPoint()
{
}
void MyPoint::setPoint(CPoint pt)
{
	this->pt = pt;
}
void MyPoint::setColor(COLORREF clr)
{
	this->clr = clr;
}
void MyPoint::setRect(bool rect)
{
	this->rect = rect;
}
bool MyPoint::getRect()
{
	return this->rect;
}
CPoint MyPoint::getPoint()
{
	return this->pt;
}
COLORREF MyPoint::getColor()
{
	return this->clr;
}
