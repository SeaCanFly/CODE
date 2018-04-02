#pragma once
class PointList
{
public:
	PointList();
	~PointList();
	CList<CPoint,CPoint&>plist;
	void drawSavePoint(CDC*, CPoint);
	void drawPoint(CDC*, CPoint);
	void cleenPoint(CPoint, CPoint);
};

