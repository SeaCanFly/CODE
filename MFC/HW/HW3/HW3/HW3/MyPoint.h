#pragma once
class MyPoint
{
private:
	CPoint pt;
	COLORREF clr;
	bool rect;
public:
	MyPoint();
	~MyPoint();
	void setPoint(CPoint);
	void setColor(COLORREF);
	void setRect(bool);
	bool getRect();
	CPoint getPoint();
	COLORREF getColor();
};

