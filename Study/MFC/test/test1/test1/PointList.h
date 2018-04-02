#pragma once
class PointList
{
public:
	PointList();
	~PointList();
	CList<CPoint, CPoint&>plist;
	CPoint pt;
	void drawPoint(CDC*);
	void drawSavePoint(CDC*,CPoint);
	void cleanPoint(CPoint ,CPoint);
};

