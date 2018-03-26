#pragma once
class PointList
{
public:
	PointList();
	~PointList();
	CPoint orip;
	CPoint endp;
	CBrush brush;
	void draw(CDC*);

};

