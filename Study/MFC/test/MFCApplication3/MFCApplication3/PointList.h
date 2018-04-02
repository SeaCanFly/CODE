#pragma once
class PointList
{
public:
	PointList();
	~PointList();
	CPoint sp, ep;
	CBrush brush;
	void draw(CDC*);
};

