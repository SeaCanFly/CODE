#pragma once
#include "MyPoint.h"
class Line
{	
private:
	CList<MyPoint>point_list;
public:
	Line();
	~Line();
	void showLine(CDC*);
	void savePoint(MyPoint);
	void delMyPoint(POSITION);
	MyPoint getMyPoint(POSITION);
	CList<MyPoint>& getLine();
};

