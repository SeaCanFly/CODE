#include "stdafx.h"
#include "Line.h"
#include "MyPoint.h"

Line::Line()
{
}


Line::~Line()
{
}
MyPoint Line::getMyPoint(POSITION pos)
{
	return point_list.GetAt(pos);
}
CList<MyPoint>& Line::getLine()
{
	return point_list;
}
void Line::delMyPoint(POSITION pos)
{
	point_list.RemoveAt(pos);
}
void Line::showLine(CDC* pdc)
{
	int num = point_list.GetCount();
	CString str;
	str.Format(_T("%d"), num);
	pdc->TextOutW(1, 1, str);

	POSITION pos = point_list.GetHeadPosition();
	while (pos != 0)
	{
		MyPoint temp = getMyPoint(pos);
		CPoint ptemp = temp.getPoint();
		COLORREF pclr = temp.getColor();
		bool rect = temp.getRect();
		CPen pen(PS_SOLID,5,pclr);
		pdc->SelectObject(&pen);
		if(rect)
		pdc->Rectangle(ptemp.x-2.5,ptemp.y-2.5,ptemp.x+2.5,ptemp.y+2.5);
		else
		pdc->Ellipse(ptemp.x-2.5,ptemp.y-2.5,ptemp.x+2.5,ptemp.y+2.5);
		point_list.GetNext(pos);
	}
}
void Line::savePoint(MyPoint pt)
{
	point_list.AddTail(pt);
}
