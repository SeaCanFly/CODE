#include "stdafx.h"
#include "PointList.h"


PointList::PointList()
{
}


PointList::~PointList()
{
}
void PointList::drawPoint(CDC* pdc)
{
	int num = plist.GetCount();
	for (int i = 0; i < num; i++)
	{
		POSITION pos = plist.FindIndex(i);
		pt = plist.GetAt(pos);
		pdc->SetPixelV(pt, RGB(255, 0, 0));
	}
}
void PointList::drawSavePoint(CDC* pdc,CPoint ps)
{
	pdc->SetPixel(ps, RGB(255, 0, 0));
	plist.AddHead(ps);
}
void PointList::cleanPoint(CPoint sp, CPoint ep)
{
	int num = plist.GetCount();
	for (int i = 0; i < num; i++)
	{
		POSITION pos = plist.FindIndex(i);
		pt = plist.GetAt(pos);
		if ((pt.x - sp.x)*(pt.x - ep.x) < 0 && (pt.y - sp.y)*(pt.y - ep.y) < 0)
		{
			plist.RemoveAt(pos);
			num--;
			i--;
		}
	}
}