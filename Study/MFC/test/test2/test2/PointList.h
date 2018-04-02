#pragma once
class PointList
{
public:
	PointList();
	~PointList();
	CPoint startp, endp;
	CBrush brush;
	void draw(CDC*);
};

