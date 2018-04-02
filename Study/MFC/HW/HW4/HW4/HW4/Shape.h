#pragma once
class Shape
{
public:
	COLORREF m_clr;
	bool mb_shape;
	CPoint p;
	double x;
	double y;
	void fDraw(CDC* pdc);
	Shape();
	 ~Shape();
};

